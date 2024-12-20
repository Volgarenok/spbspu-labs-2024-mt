#ifndef POINT_HPP
#define POINT_HPP
#include <ostream>

namespace piyavkin
{
  struct point_t
  {
    double x;
    double y;
  };
  std::ostream& operator<<(std::ostream& out, const point_t& p);
  
  struct rectangle_t
  {
    point_t ll;
    point_t ur;
  };
  std::ostream& operator<<(std::ostream& out, const rectangle_t& r);
}
#endif