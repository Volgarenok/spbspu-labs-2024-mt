#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include "circle.hpp"

namespace kravchenko
{
  using CircleSet = std::unordered_set< std::string, Circle >;
  using GlobalSet = std::unordered_set< std::string, CircleSet >;
  using CircleData = std::vector< Circle >;

  void area(int fdsToCompute, const GlobalSet& sets, std::istream& in);
  void status(int fdsToCompute, const GlobalSet& sets, std::istream& in, std::ostream& out);
  void wait(int fdsToCompute, const GlobalSet& sets, std::istream& in, std::ostream& out);
}

#endif