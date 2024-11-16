#ifndef AREAPROCESSING_HPP
#define AREAPROCESSING_HPP
#include <vector>
#include "point.hpp"

namespace redko
{
  using point_it = std::vector< Point >::iterator;
  using size_it = std::vector< size_t >::iterator;

  bool isPointInCircle(Point p, int radius);
  void fillWithRandomPoints(double radius, size_t tries, int seed, std::vector< Point > & dest);
  void countPointsInCircle(int radius, point_it begin, size_t numOfPoints, size_it dest);
  double calculateCircleArea(int radius, size_t numOfThreads, size_t tries, int seed);
}

#endif
