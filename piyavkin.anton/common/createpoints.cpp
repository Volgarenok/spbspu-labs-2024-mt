#include "createpoints.hpp"

void piyavkin::createPoints(std::minstd_rand& gen, data_t& points, double r, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    std::uniform_real_distribution< double > dis(0, r);
    points.push_back({dis(gen), dis(gen)});
  }
}
