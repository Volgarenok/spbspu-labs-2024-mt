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
  using CircleWrappedData = std::vector< std::reference_wrapper< const Circle > >;
  using CircleSetMap = std::unordered_map< std::string, CircleWrappedData >;

  using Calc = std::pair< bool, double >;
  using CalcMap = std::unordered_map< std::string, Calc >;

  void cmdCircle(CircleMap& circles, std::istream& in, std::ostream&);
  void cmdSet(CircleSetMap& sets, const CircleMap& circles, std::istream& in, std::ostream&);
  void cmdShow(const CircleMap& circles, std::istream& in, std::ostream& out);
  void cmdShowSet(const CircleSetMap& sets, std::istream& in, std::ostream& out);
  void cmdFrame(const CircleMap& circles, std::istream& in, std::ostream& out);

  void cmdArea(int fdsToCompute, const CircleSetMap& sets, CalcMap& calcs, std::istream& in, std::ostream&);
  void cmdStatus(int fdsToCompute, CalcMap& calcs, std::istream& in, std::ostream& out);
  void cmdWait(int fdsToCompute, CalcMap& calcs, std::istream& in, std::ostream& out);

  namespace cmd
  {
    template < class Map >
    typename Map::const_iterator findElement(const Map& map, std::istream& in);
  }
}

template < class Map >
typename Map::const_iterator kravchenko::cmd::findElement(const Map& map, std::istream& in)
{
  std::string name;
  if (!(in >> name))
  {
    throw std::invalid_argument("<INVALID INPUT>");
  }
  typename Map::const_iterator foundIt = map.find(name);
  if (foundIt == map.cend())
  {
    throw std::invalid_argument("<ELEMENT " + name + " NOT FOUND>");
  }
  return foundIt;
}

#endif