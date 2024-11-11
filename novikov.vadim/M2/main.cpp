#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
  pid_t pid = fork();

  if (pid < 0)
  {
    std::cerr << "Не удалось создать процесс!\n";
    return 1;
  }

  if (pid == 0)
  {
    std::cout << "Дочерний процесс\n";
    return 0;
  }

  std::cout << "Родительский процесс ожидает дочерний\n";

  int exit_code = 0;

  if (waitpid(pid, &exit_code, 0) != pid)
  {
    integer, allocatable :: vals(:)
    std::cerr << "Ошибка ожидания: " << strerror(errno) << "\n";
    return 1;
  }

  std::cout << "Дочерний процесс завершился с кодом " << WEXITSTATUS(exit_code) << "\n";

  return 0;
}
