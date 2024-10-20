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
  size_t calculateTargetPoints(size_t seed, size_t tries, size_t skips, size_t radius);
}

#endif
