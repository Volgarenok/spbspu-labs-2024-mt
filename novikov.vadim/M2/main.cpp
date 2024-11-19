#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <limits>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <StringFunctions.hpp>
#include "CommandFunctions.hpp"

int main(int argc, const char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Некорректное кол-во параметров!\n";
    return -1;
  }

  size_t seed = 0;
  
  if (argc == 2)
  {
    try
    {
      seed = novikov::parseSizeType(argv[1]);
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what() << "\n";
      return -1;
    }
  }

  std::cout << seed << "\n";

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

  using namespace novikov;
  circle_collection_t circles;
  circle_set_collection_t circle_sets;

  using command_t = std::function< void(std::istream&, std::ostream&) >;
  std::unordered_map< std::string, command_t > commands;
  {
    using namespace std::placeholders;
    commands["circle"] = std::bind(cmd::circle, _1, _2, std::ref(circles));
    commands["set"] = std::bind(cmd::set, _1, _2, std::ref(circle_sets));
    commands["show"] = std::bind(cmd::show, _1, _2, std::cref(circles));
    commands["showset"] = std::bind(cmd::showset, _1, _2, std::cref(circles), std::cref(circle_sets));
    commands["frame"] = std::bind(cmd::frame, _1, _2, std::cref(circles));
  }

  std::string cmd;

  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout);
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what() << "\n";
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::cout << "Родительский процесс ожидает дочерний\n";

  int exit_code = 0;

  if (waitpid(pid, &exit_code, 0) != pid)
  {
    std::cerr << "Ошибка ожидания: " << strerror(errno) << "\n";
    return 1;
  }

  std::cout << "Дочерний процесс завершился с кодом " << WEXITSTATUS(exit_code) << "\n";

  return 0;
}
