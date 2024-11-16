#include <string>
#include <iostream>
#include <functional>
#include <iomanip>
#include "userCommands.hpp"

int main(int argc, char ** argv)
{
  long long seed = 0;
  if (argc == 2)
  {
    try
    {
      seed = std::stoll(argv[1]);
    }
    catch (const std::exception &)
    {
      std::cerr << "invalid seed\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "wrong number of parameters\n";
    return 1;
  }

  if (seed < 0)
  {
    std::cerr << "negative seed\n";
    return 2;
  }
  std::map < std::string, std::function< void(std::istream &, redko::map_t &, redko::set_t &, std::map< std::string, redko::Calculation > &, std::ostream &) > > commands;
  {
    using namespace std::placeholders;
    commands["circle"] = std::bind(redko::createCircle, _1, _2, _3, _4, _5);
    commands["set"] = std::bind(redko::createSet, _1, _2, _3, _4, _5);
    commands["show"] = std::bind(redko::showCircle, _1, _2, _3, _4, _5);
    commands["showset"] = std::bind(redko::showSet, _1, _2, _3, _4, _5);
    commands["frame"] = std::bind(redko::showCircleFrame, _1, _2, _3, _4, _5);
    commands["frameset"] = std::bind(redko::showSetFrame, _1, _2, _3, _4, _5);
    commands["area"] = std::bind(redko::calculateSetArea, _1, _2, _3, _4, _5);
    commands["status"] = std::bind(redko::showStatus, _1, _2, _3, _4, _5);
    commands["wait"] = std::bind(redko::wait, _1, _2, _3, _4, _5);
  }
  redko::map_t sets;
  redko::set_t circles;
  std::map< std::string, redko::Calculation > calcs;

  std::cout << std::fixed << std::setprecision(3);
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, sets, circles, calcs, std::cout);
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "invalid command\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error & e)
    {
      std::cerr << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
