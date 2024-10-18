#include <iostream>
#include <limits>
#include <functional>
#include "commands.hpp"

int main()
{
  using namespace piyavkin;
  std::map< std::string, Circle > circles;
  std::map< std::string, Set > sets;
  std::map< std::string, std::function< void(std::istream&) > > cmd;
  cmd["circle"] = std::bind(inputCircle, std::placeholders::_1, std::ref(circles));
  cmd["show"] = std::bind(outputCircle, std::placeholders::_1, std::ref(std::cout), std::cref(circles));
  cmd["frame"] = std::bind(outputFrameCircle, std::placeholders::_1, std::ref(std::cout), std::cref(circles));
  cmd["set"] = std::bind(inputSet, std::placeholders::_1, std::ref(sets), std::cref(circles));
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
  std::cout << sets.at("s1").set_[0].center_ << ' ' << sets.at("s1").set_[0].radius_;
}
