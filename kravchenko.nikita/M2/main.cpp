#include <cstring>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <sys/wait.h>
#include <unistd.h>
#include "commands.hpp"
#include "compute_handler.hpp"
#include "pipe_channel.hpp"

int main()
{
  int fdsToCompute[2] = {};
  int fdsToUser[2] = {};
  if (pipe(fdsToCompute) < 0 || pipe(fdsToUser) < 0)
  {
    std::cerr << "Pipe creation error: " << strerror(errno) << '\n';
    return 1;
  }
  pid_t cpid = fork();
  if (cpid == -1)
  {
    close(fdsToCompute[0]);
    close(fdsToCompute[1]);
    close(fdsToUser[0]);
    close(fdsToUser[1]);
    std::cerr << "Process fork error: " << strerror(errno) << '\n';
    return 1;
  }
  using namespace kravchenko;
  if (cpid == 0)
  {
    PipeChannel channel(fdsToCompute, fdsToUser);

    CalcMap computeCalcs;
    QueryType currentQuery;
    channel.pop(currentQuery);
    while (currentQuery != QueryType::QUIT)
    {
      switch (currentQuery)
      {
      case QueryType::AREA:
        handleArea(channel, computeCalcs);
        break;
      default:
        std::cerr << "<INVALID QUERY>\n";
        return 1;
      }
      channel.pop(currentQuery);
    }
  }
  else
  {
    PipeChannel channel(fdsToUser, fdsToCompute);

    CircleMap circles;
    CircleSetMap sets;
    CalcMap userCalcs;
    std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
    {
      using namespace std::placeholders;
      cmds["circle"] = std::bind(cmdCircle, std::ref(circles), _1, _2);
      cmds["set"] = std::bind(cmdSet, std::ref(sets), std::cref(circles), _1, _2);
      cmds["show"] = std::bind(cmdShow, std::cref(circles), _1, _2);
      cmds["showset"] = std::bind(cmdShowSet, std::cref(sets), _1, _2);
      cmds["frame"] = std::bind(cmdFrame, std::cref(circles), _1, _2);
      cmds["frameset"] = std::bind(cmdFrameSet, std::cref(sets), _1, _2);
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

    if (waitpid(cpid, nullptr, 0) != cpid)
    {
      std::cerr << "Process wait failed: " << strerror(errno) << '\n';
      return 1;
    }
  }
  return 0;
}