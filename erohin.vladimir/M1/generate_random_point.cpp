#include "generate_random_point.hpp"

erohin::point_t erohin::generateRandomPoint(std::minstd_rand & generator, size_t limit)
{
  std::uniform_real_distribution< double > distr(0, limit);
  return point_t{ distr(generator), distr(generator) };
}
