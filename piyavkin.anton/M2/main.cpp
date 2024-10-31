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
#include "unlinkfileguard.hpp"

int main()
{
  const char* path = "piyavkin.anton/M2/1.socket";
  pid_t child_pid = fork();
  std::cout << child_pid << '\n';
  if (child_pid < 0)
  {
    std::cerr << "Fork has failed\n";
    return 1;
  }
  else if (child_pid == 0)
  {
    int listening{socket(AF_UNIX, SOCK_STREAM, 0)};
    if (listening < 0)
    {
      std::cerr << "Child process has failed\n";
      return 1;
    }
    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    piyavkin::UnlinkFileGuard fg(listening, addr.sun_path);
    if (bind(listening, reinterpret_cast< const sockaddr* >(&addr), sizeof(addr)) < 0)
    {
      std::cerr << strerror(errno) << '\n';
      return 1;
    }
    if (listen(listening, 1024) < 0)
    {
      std::cerr << strerror(errno) << '\n';
      return 1;
    }
    int sock{accept(listening, nullptr, 0)};
    if (sock < 0)
    {
      std::cerr << "Acceptance not completed\n";
      return 1;
    }
    char buffer[1024] = {};
    int sizeMsg = recv(sock, buffer, 1024, 0); //в последний попробовать MSG_WAITALL(Этот флаг просит подождать, пока не придет полное запрошенное количество данных)
    if (sizeMsg < 0)
    {
      std::cerr << "гг";
      return 1;
    }
    std::cout << buffer << '\n';
  }
  else
  {
    char buffer[] = "какашка";
    int sock{socket(AF_UNIX, SOCK_STREAM, 0)};
    if (!sock)
    {
      std::cerr << "Failed to create socket\n";
      return 2;
    }
    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    piyavkin::UnlinkFileGuard fg(sock, addr.sun_path);
    sleep(1);
    if (connect(sock, reinterpret_cast< sockaddr* >(&addr), sizeof(addr)) < 0)
    {
      std::cerr << "Connection failed: " << strerror(errno) << '\n';
      std::cerr << addr.sun_path << '\n';
      return 2;
    }
    int bytes_sent = send(sock, buffer, strlen(buffer), MSG_NOSIGNAL);
    if (bytes_sent < 0)
    {
      std::cerr << "Error sending data\n";
      close(sock);
      return 1;
    }
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
