#ifndef POINT_HPP
#define POINT_HPP
#include <ostream>

namespace redko
{
  struct Point
  {
    double x;
    double y;
  };
  std::ostream & operator<<(std::ostream & out, const Point & point);
}

#endif
