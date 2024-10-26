#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iosfwd>
#include <cstddef>

namespace novikov
{
  struct CircleInput
  {
    size_t radius;
    size_t thread_count;
  };

  std::istream& operator>>(std::istream& in, CircleInput& circle);
}

#endif
