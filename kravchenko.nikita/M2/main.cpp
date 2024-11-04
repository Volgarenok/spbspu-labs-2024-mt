#include <cstring>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <sys/wait.h>
#include <unistd.h>
#include "commands.hpp"
#include "pipe_channel.hpp"
#include "queries.hpp"

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }
  size_t generatorSeed = 0;
  if (argc == 2)
  {
    try
    {
      generatorSeed = std::stoull((argv[1][0] != '-') ? argv[1] : "invalid");
    }
    catch (...)
    {
      std::cerr << "Invalid seed\n";
      return 1;
    }
  }

  struct sigaction epipe = {};
  epipe.sa_handler = SIG_IN;
  if (sigaction(SIGPIPE, &epipe, NULL) < 0)
  {
    std::cerr << "Failed to install handler: " << strerror(errno) << '\n';
    return 1;
  }

  int fdsUserToCompute[2] = {};
  int fdsComputeToUser[2] = {};
  if (pipe(fdsUserToCompute) < 0 || pipe(fdsComputeToUser) < 0)
  {
    std::cerr << "Pipe creation error: " << strerror(errno) << '\n';
    return 1;
  }

  pid_t childPid = fork();
  if (childPid == -1)
  {
    close(fdsUserToCompute[0]);
    close(fdsUserToCompute[1]);
    close(fdsComputeToUser[0]);
    close(fdsComputeToUser[1]);
    std::cerr << "Process fork error: " << strerror(errno) << '\n';
    return 1;
  }

  using namespace kravchenko;
  if (childPid == 0)
  {
    PipeChannel channel(fdsUserToCompute, fdsComputeToUser);
    GeneratorT generator(generatorSeed);
    ThreadMap tasks;
    CalcMap calcs;

    std::unordered_map< QueryType, std::function< void(PipeChannel&, CalcMap&, ThreadMap&) > > queries;
    {
      using namespace std::placeholders;
      queries[QueryType::AREA] = std::bind(queryArea, _1, _2, _3, std::ref(generator));
      queries[QueryType::STATUS] = queryStatus;
      queries[QueryType::WAIT] = queryWait;
    }

    QueryType currentQuery;
    channel.pop(currentQuery);
    while (currentQuery != QueryType::QUIT)
    {
      try
      {
        queries.at(currentQuery)(channel, calcs, tasks);
        channel.pop(currentQuery);
      }
      catch (const std::out_of_range& e)
      {
        std::cout << "<INVALID QUERY>\n";
        break;
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << '\n';
        break;
      }
    }
    for (auto& task : tasks)
    {
      task.second.join();
    }
  }
  else
  {
    PipeChannel channel(fdsComputeToUser, fdsUserToCompute);
    CircleMap circles;
    CircleSetMap sets;
    CalcMap calcs;

    std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
    {
      using namespace std::placeholders;
      cmds["circle"] = std::bind(cmdCircle, std::ref(circles), _1, _2);
      cmds["set"] = std::bind(cmdSet, std::ref(sets), std::cref(circles), _1, _2);
      cmds["show"] = std::bind(cmdShow, std::cref(circles), _1, _2);
      cmds["showset"] = std::bind(cmdShowSet, std::cref(sets), _1, _2);
      cmds["frame"] = std::bind(cmdFrame, std::cref(circles), _1, _2);
      cmds["frameset"] = std::bind(cmdFrameSet, std::cref(sets), _1, _2);

      cmds["area"] = std::bind(cmdArea, std::ref(channel), std::cref(sets), std::ref(calcs), _1, _2);
      cmds["status"] = std::bind(cmdSync< false >, std::ref(channel), std::ref(calcs), _1, _2);
      cmds["wait"] = std::bind(cmdSync< true >, std::ref(channel), std::ref(calcs), _1, _2);
    }

    std::string cmd;
    while (std::cin >> cmd)
    {
      try
      {
        cmds.at(cmd)(std::cin, std::cout);
      }
      catch (const std::out_of_range& e)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      catch (const std::invalid_argument& e)
      {
        std::cout << e.what() << '\n';
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << '\n';
        break;
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    channel.push(QueryType::QUIT);

    if (waitpid(childPid, nullptr, 0) != childPid)
    {
      std::cerr << "Process wait failed: " << strerror(errno) << '\n';
      return 1;
    }
  }
  return 0;
}
