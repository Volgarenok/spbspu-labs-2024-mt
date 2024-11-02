#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <cstddef>
#include <iosfwd>

namespace novikov
{
  struct Circle
  {
    size_t radius;
    ptrdiff_t x;
    ptrdiff_t y;
  };

  std::istream& operator>>(std::istream& in, Circle& circle);
  std::ostream& operator<<(std::ostream& out, const Circle& circle);
};

#endif
