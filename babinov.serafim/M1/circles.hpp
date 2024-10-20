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
  double getSquare(CircleData data, size_t seed, size_t tries);
}

#endif
