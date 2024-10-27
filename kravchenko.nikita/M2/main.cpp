#include <cstring>
#include <iostream>
#include <limits>
#include <sys/wait.h>
#include <unistd.h>
#include "commands.hpp"
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

    Circle test;
    pipePop(fdsToCompute[0], test);
    std::cout << "Circle from user:\n";
    std::cout << test << '\n';

    std::cout << "Compute closed\n";
  }
  else
  {
    PipeGuard< false > userGuard(fdsToUser);
    PipeGuard< true > computeGuard(fdsToCompute);

    Circle test;
    std::cout << "Enter circle:\n";
    std::cin >> test;
    pipePush(fdsToCompute[1], test);

    if (waitpid(cpid, nullptr, 0) != cpid)
    {
      std::cerr << "Process wait failed: " << strerror(errno) << '\n';
      return 1;
    }
    std::cout << "User closed\n";
  }
  return 0;
}