#ifndef CIRCLES_HPP
#define CIRCLES_HPP
#include <istream>

namespace babinov
{
  struct CircleData
  {
    int radius;
    int nThreads;
  };
  std::istream& operator>>(std::istream& in, CircleData& data);
}

#endif
