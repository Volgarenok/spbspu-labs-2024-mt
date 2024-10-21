#include <iostream>
#include <limits>
#include <functional>
#include "commands.hpp"

int main()
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
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
