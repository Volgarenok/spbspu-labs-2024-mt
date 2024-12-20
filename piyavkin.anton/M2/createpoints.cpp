#include "createpoints.hpp"

void piyavkin::createPoints(std::minstd_rand& gen, data_t& points, const rectangle_t& r, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    std::uniform_real_distribution< double > dis1(r.ll.x, r.ur.x);
    std::uniform_real_distribution< double > dis2(r.ll.y, r.ur.y);
    points.push_back({dis1(gen), dis2(gen)});
  }
}