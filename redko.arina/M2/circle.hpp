#ifndef BASETYPES_HPP
#define BASETYPES_HPP
#include "point.hpp"
#include <set>
#include <map>

namespace redko
{
  struct Circle
  {
    Circle(const std::string & name):
      name(name),
      radius(1),
      center({ 0, 0 })
    {}
    Circle(const std::string & name, int radius, Point point):
      name(name),
      radius(radius),
      center(point)
    {}
    std::string name;
    int radius;
    Point center;
  };

  using set_t = std::set< Circle >;
  using map_t = std::map< std::string, std::set< Circle > >;

  using circle_it = set_t::iterator;
  using set_it = map_t::iterator;

  std::ostream & operator<<(std::ostream & out, const Circle & circle);

  bool operator<(const std::string & name, const Circle & circle);
  bool operator<(const Circle & circle, const std::string & name);
  bool operator<(const Circle & firstCircle, const Circle & secondCircle);
}

#endif
