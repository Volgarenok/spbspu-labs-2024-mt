#ifndef AREAPROCESSING_HPP
#define AREAPROCESSING_HPP
#include <utility>
#include <cstdlib>

namespace redko
{
  using point_t = std::pair< double, double >;

  bool isPointInCircle(point_t p, double radius);
  double calculateCircleArea(double radius, size_t tries);
}

#endif
