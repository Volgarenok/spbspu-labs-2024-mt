#include <cstring>
#include <iostream>
#include <limits>
#include <sys/wait.h>
#include <unistd.h>
#include "commands.hpp"
#include "pipe_communication.hpp"

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
  if (cpid == 0) // Compute (child)
  {
    close(fdsToCompute[1]);
    close(fdsToUser[0]);
    fdsToCompute[1] = -1;
    fdsToUser[0] = -1;

    using namespace kravchenko;
    Circle test;
    pipePop(fdsToCompute[0], test);
    std::cout << "Circle from user:\n";
    std::cout << test << '\n';

    close(fdsToCompute[0]);
    close(fdsToUser[1]);
    std::cout << "Compute closed\n";
  }
  else // User (parent)
  {
    close(fdsToCompute[0]);
    close(fdsToUser[1]);
    fdsToCompute[0] = -1;
    fdsToUser[1] = -1;

    using namespace kravchenko;
    Circle test;
    std::cout << "Enter circle:\n";
    std::cin >> test;
    pipePush(fdsToCompute[1], test);

    close(fdsToCompute[1]);
    close(fdsToUser[0]);

    if (waitpid(cpid, nullptr, 0) != cpid)
    {
      std::cerr << "Process wait failed: " << strerror(errno) << '\n';
      return 1;
    }
    std::cout << "User closed\n";
  }
  return 0;
}