#include <cstring>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sys/wait.h>
#include <unistd.h>
#include "commands.hpp"
#include "compute_handler.hpp"
#include "pipe_communication.hpp"
#include "pipe_guard.hpp"

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
    std::cerr << "Process fork error: " << strerror(errno) << '\n';
    return 1;
  }
  using namespace kravchenko;
  if (cpid == 0)
  {
    PipeGuard< true > userGuard(fdsToUser);
    PipeGuard< false > computeGuard(fdsToCompute);

    CalcMap computeCalcs;
    QueryType currentQuery;
    pipePop(fdsToCompute[0], currentQuery);
    while (currentQuery != QueryType::QUIT)
    {
      switch (currentQuery)
      {
      case QueryType::AREA:
        handleArea(fdsToCompute[0], computeCalcs);
        break;
      default:
        std::cerr << "<INVALID QUERY>\n";
        return 1;
      }
      pipePop(fdsToCompute[0], currentQuery);
    }
  }
  else
  {
    PipeGuard< false > userGuard(fdsToUser);
    PipeGuard< true > computeGuard(fdsToCompute);

    CircleMap circles;
    CircleSetMap sets;
    CalcMap userCalcs;
    std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
    {
      using namespace std::placeholders;
      cmds["circle"] = std::bind(cmdCircle, std::ref(circles), _1, _2);
      cmds["set"] = std::bind(cmdSet, std::ref(sets), std::cref(circles), _1, _2);

      cmds["area"] = std::bind(cmdArea, fdsToCompute[1], std::cref(sets), std::ref(userCalcs), _1, _2);
      // cmds["status"] = std::bind(cmdStatus, std::ref(userCalcs), _1, _2);
      // cmds["wait"] = std::bind(cmdWait, std::ref(userCalcs), _1, _2);
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
        std::cout << e.what() << '\n';
        break;
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    pipePush(fdsToCompute[1], QueryType::QUIT);

    if (waitpid(cpid, nullptr, 0) != cpid)
    {
      std::cerr << "Process wait failed: " << strerror(errno) << '\n';
      return 1;
    }
  }
  return 0;
}