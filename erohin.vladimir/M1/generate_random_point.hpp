#ifndef GENERATE_RANDOM_POINT_HPP
#define GENERATE_RANDOM_POINT_HPP

#include <random>

namespace erohin
{
  struct point_t
  {
    double x;
    double y;
  };

  point_t generateRandomPoint(std::minstd_rand & generator, size_t limit);
}

#endif
