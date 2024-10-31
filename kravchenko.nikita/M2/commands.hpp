#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "circle.hpp"

namespace kravchenko
{
  using CircleMap = std::unordered_map< std::string, Circle >;
  using CirclePair = CircleMap::value_type;
  using CircleWrappedData = std::vector< std::reference_wrapper< const CirclePair > >;
  using CircleSetMap = std::unordered_map< std::string, CircleWrappedData >;

  using Calc = std::pair< bool, double >;
  using CalcMap = std::unordered_map< std::string, Calc >;

  void cmdCircle(CircleMap& circles, std::istream& in, std::ostream&);
  void cmdSet(CircleSetMap& sets, const CircleMap& circles, std::istream& in, std::ostream&);

  void cmdArea(int fdsToCompute, const CircleSetMap& sets, CalcMap& calcs, std::istream& in, std::ostream&);
  void cmdStatus(int fdsToCompute, CalcMap& calcs, std::istream& in, std::ostream& out);
  void cmdWait(int fdsToCompute, CalcMap& calcs, std::istream& in, std::ostream& out);
}

#endif