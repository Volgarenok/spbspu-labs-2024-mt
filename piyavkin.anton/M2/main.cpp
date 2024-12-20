#include <cstring>
#include <iostream>
#include <functional>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <getpositivenum.hpp>
#include "commands.hpp"
#include "childcommands.hpp"
#include "unlinkfileguard.hpp"

int main(int argc, char* argv[])
{
  if (argc > 3 || argc < 1)
  {
    std::cerr << "Command line parameters entered incorrectly\n";
    return 3;
  }
  size_t seed = 0;
  if (argc == 2)
  {
    seed = piyavkin::getPositiveNum(argv[1]);
  }
  
  const char* path = "piyavkin.anton/M2/1.socket";
  struct sockaddr_un addr = {0};
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, path, sizeof(addr.sun_path));
  
  pid_t child_pid = fork();
  using namespace piyavkin;
  if (child_pid < 0)
  {
    std::cerr << "Fork has failed\n";
    return 1;
  }
  else if (child_pid == 0)
  {
    int listening{socket(AF_UNIX, SOCK_STREAM, 0)};
    if (listening <= 0)
    {
      std::cerr << "Server creation is failed: " << strerror(errno) << '\n';
      return 2;
    }
    
    if (bind(listening, reinterpret_cast< const sockaddr* >(&addr), sizeof(addr)) < 0)
    {
      std::cerr << "Binding failed: " << strerror(errno) << '\n';
      return 2;
    }
    
    UnlinkFileGuard fg(listening, addr.sun_path);
    if (listen(listening, 1000) < 0)
    {
      std::cerr << "Listening failed: " << strerror(errno) << '\n';
      return 2;
    }
    
    int sock{accept(listening, nullptr, 0)};
    if (sock <= 0)
    {
      close(sock);
      std::cerr << "Acceptance not completed: " << strerror(errno) << '\n';
      return 2;
    }
    
    std::map< char, std::function< void(calc_t&, const std::string&, std::map< std::string, std::thread >&) > > childCmd;
    calc_t calcs;
    std::minstd_rand gen(seed);
    std::map< std::string, std::thread > threads;
    
    {
      using namespace std::placeholders;
      childCmd['a'] = std::bind(calculateAreaSet, _1, std::ref(gen), _2, _3);
      childCmd['s'] = std::bind(sendStatus, _1, _2, sock, _3);
      childCmd['w'] = std::bind(waitStatus, _1, _2, sock, _3);
    }
    
    char buffer[1000] = {};
    while (true)
    {
      if (recv(sock, buffer, 1000, 0) < 0)
      {
        close(sock);
        std::cerr << "Data not received: " << strerror(errno) << '\n';
        return 3;
      }
      try
      {
        std::string tn(std::string(buffer).substr(2));
        childCmd.at(buffer[0])(calcs, tn, threads);
        memset(buffer, '\0', sizeof(buffer));
      }
      catch (const std::out_of_range&)
      {
        close(sock);
        for (auto&& x: threads)
        {
          x.second.join();
        }
        return 0;
      }
      catch (const std::exception& e)
      {
        close(sock);
        for (auto&& x: threads)
        {
          x.second.join();
        }
        std::cerr << e.what() << '\n';
        return 4;
      }
    }
  }
  else
  {
    int sock{socket(AF_UNIX, SOCK_STREAM, 0)};
    if (sock <= 0)
    {
      std::cerr << "Failed to create socket: " << strerror(errno) << '\n';
      return 2;
    }
    UnlinkFileGuard fg(sock, addr.sun_path);
    
    sleep(1);
    if (connect(sock, reinterpret_cast< sockaddr* >(&addr), sizeof(addr)) < 0)
    {
      std::cerr << "Connection failed: " << strerror(errno) << '\n';
      return 2;
    }
    
    circle_t circles;
    set_t sets;
    calc_t calcs;
    std::map< std::string, std::function< void(std::istream&) > > cmd;
    {
      using namespace std::placeholders;
      cmd["circle"] = std::bind(input< Circle, circle_t& >, _1, std::ref(circles));
      cmd["show"] = std::bind(output< Circle >, _1, std::ref(std::cout), std::cref(circles));
      cmd["frame"] = std::bind(outputFrame< Circle >, _1, std::ref(std::cout), std::cref(circles));
      cmd["set"] = std::bind(input< Set, set_t&, const circle_t& >, _1, std::ref(sets), std::cref(circles));
      cmd["showset"] = std::bind(output< Set >, _1, std::ref(std::cout), std::cref(sets));
      cmd["frameset"] = std::bind(outputFrame< Set >, _1, std::ref(std::cout), std::cref(sets));
      cmd["area"] = std::bind(calcArea, _1, std::ref(sets), std::ref(calcs), sock);
      cmd["status"] = std::bind(recStatus, _1, std::ref(std::cout), std::ref(calcs), sock, false);
      cmd["wait"] = std::bind(recStatus, _1, std::ref(std::cout), std::ref(calcs), sock, true);
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
    
    const char* m = "exit";
    if (send(sock, m, std::strlen(m), 0) < 0)
    {
      std::cerr << "The child process failed to terminate: " << strerror(errno) << '\n';
      return 4;
    }
  }
}
