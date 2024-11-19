#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Point.hpp"
#include "Frame.hpp"

namespace novikov
{
  struct Circle
  {
    size_t radius;
    Point center;
  };

  std::istream& operator>>(std::istream& in, Circle& circle);
  std::ostream& operator<<(std::ostream& out, const Circle& circle);
  Frame getFrame(const Circle& circle);
};

#endif
