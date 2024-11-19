#ifndef POINT_HPP
#define POINT_HPP

#include <cstddef>
#include <iosfwd>

namespace novikov
{
  struct Point
  {
    ptrdiff_t x;
    ptrdiff_t y;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);
}

#endif
