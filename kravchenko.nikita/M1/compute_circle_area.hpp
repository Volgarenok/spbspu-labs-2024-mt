#ifndef COMPUTE_CIRCLE_AREA
#define COMPUTE_CIRCLE_AREA

#include <random>

namespace kravchenko
{
  double computeCircleArea(size_t tries, std::minstd_rand& generator, double radius, size_t threads);
}

#endif
