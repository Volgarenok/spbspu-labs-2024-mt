#ifndef FRAME_HPP
#define FRAME_HPP

#include "Point.hpp"
#include <iosfwd>

namespace novikov
{
  struct Frame
  {
    Point left_down;
    Point up_right;
  };

  std::ostream& operator<<(std::ostream& out, const Frame& frame);
}

#endif
