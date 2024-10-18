#include <iostream>
#include <limits>
#include <functional>
#include "circle.hpp"
#include "set.hpp"
#include "commands.hpp"

int main()
{
  using namespace piyavkin;
  std::map< std::string, Circle > circles;
  std::map< std::string, Set > sets;
  std::map< std::string, std::function< void(std::istream&) > > cmd;
  cmd["circle"] = std::bind(input< Circle >, std::placeholders::_1, std::ref(circles));
  cmd["show"] = std::bind(output< Circle >, std::placeholders::_1, std::ref(std::cout), std::cref(circles));
  cmd["frame"] = std::bind(outputFrame< Circle >, std::placeholders::_1, std::ref(std::cout), std::cref(circles));
  cmd["set"] = std::bind(input< Set >, std::placeholders::_1, std::ref(sets), std::cref(circles));
  cmd["showset"] = std::bind(output< Set >, std::placeholders::_1, std::ref(std::cout), std::cref(sets));
  cmd["frameset"] = std::bind(outputFrame< Set >, std::placeholders::_1, std::ref(std::cout), std::cref(sets));
  std::string name;
  while (std::cin >> name)
  {
    try
    {
      cmd.at(name)(std::cin);
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
