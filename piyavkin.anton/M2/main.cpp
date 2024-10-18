#include <iostream>
#include <map>
#include <functional>
#include "circle.hpp"
#include "commands.hpp"

int main()
{
  using namespace piyavkin;
  std::map< std::string, Circle > mp;
  std::map< std::string, std::function< void(std::istream&) > > cmd;
  cmd["circle"] = std::bind(inputCircle, std::placeholders::_1, std::ref(mp));
  cmd["show"] = std::bind(outputCircle, std::placeholders::_1, std::ref(std::cout), std::cref(mp));
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
  }
}
