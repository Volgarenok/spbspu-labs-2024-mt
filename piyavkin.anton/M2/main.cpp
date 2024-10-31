#include <cerrno>
#include <iostream>
#include <limits>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <functional>
#include "commands.hpp"

int main()
{
  pid_t child_pid = fork();
  if (child_pid < 0)
  {
    std::cerr << "Fork has failed\n";
    return 1;
  }
  else if (child_pid == 0)
  {
    int listening{socket(AF_UNIX, SOCK_STREAM, 0)};
    if (!listening)
    {
      std::cerr << "Child process has failed\n";
      return 1;
    }
    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    const char* path = "/socket";
    strcpy(addr.sun_path, path);
    if (bind(listening, reinterpret_cast< const sockaddr* >(&addr), sizeof(addr)) < 0)
    {
      std::cerr << strerror(errno) << '\n';
      return 1;
    }
    // UnlinkFileGuard fg{addr.sun_path};
  }
  else
  {
    using namespace piyavkin;
    circle_t circles;
    set_t sets;
    std::map< std::string, std::function< void(std::istream&) > > cmd;
    {
      using namespace std::placeholders;
      cmd["circle"] = std::bind(input< Circle, circle_t& >, _1, std::ref(circles));
      cmd["show"] = std::bind(output< Circle >, _1, std::ref(std::cout), std::cref(circles));
      cmd["frame"] = std::bind(outputFrame< Circle >, _1, std::ref(std::cout), std::cref(circles));
      cmd["set"] = std::bind(input< Set, set_t&, const circle_t& >, _1, std::ref(sets), std::cref(circles));
      cmd["showset"] = std::bind(output< Set >, _1, std::ref(std::cout), std::cref(sets));
      cmd["frameset"] = std::bind(outputFrame< Set >, _1, std::ref(std::cout), std::cref(sets));
    }
    std::string name;
    while (std::cin >> name)
    {
      try
      {
        cmd.at(name)(std::cin);
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
