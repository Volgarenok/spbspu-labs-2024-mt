#ifndef CIRCLE_OUTPUT_HPP
#define CIRCLE_OUTPUT_HPP

#include <iosfwd>

namespace novikov
{
  struct CircleOutput
  {
    double elapsed_time;
    double area;
  };

  std::ostream& operator<<(std::ostream& out, const CircleOutput& circle);
}

#endif
