#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

int main()
{
  int fdsToCompute[2] = {};
  int fdsToUser[2] = {};
  if (pipe(fdsToCompute) < 0 || pipe(fdsToCompute) < 0)
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
  if (cpid == 0)
  {
    close(fdsToCompute[1]);
    close(fdsToUser[0]);
    fdsToCompute[1] = -1;
    fdsToUser[0] = -1;

    close(fdsToCompute[0]);
    close(fdsToUser[1]);
  }
  else
  {
    close(fdsToCompute[0]);
    close(fdsToUser[1]);
    fdsToCompute[0] = -1;
    fdsToUser[1] = -1;

    close(fdsToCompute[0]);
    close(fdsToUser[1]);
  }
  return 0;
}