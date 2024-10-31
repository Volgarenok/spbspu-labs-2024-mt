#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "circle.hpp"

namespace kravchenko
{
  using CircleMap = std::unordered_map< std::string, Circle >;
  using CircleData = std::vector< Circle >;
  using CircleSetMap = std::unordered_map< std::string, CircleData >;

  using Calc = std::pair< bool, double >;
  using CalcMap = std::unordered_map< std::string, Calc >;

  void cmdCircle(CircleMap& circles, std::istream& in, std::ostream&);

  void cmdArea(int fdsToCompute, const CircleSetMap& sets, CalcMap& calcs, std::istream& in, std::ostream&);
  void cmdStatus(int fdsToCompute, CalcMap& calcs, std::istream& in, std::ostream& out);
  void cmdWait(int fdsToCompute, CalcMap& calcs, std::istream& in, std::ostream& out);
}

#endif