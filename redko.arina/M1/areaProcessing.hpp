#ifndef AREAPROCESSING_HPP
#define AREAPROCESSING_HPP
#include <cstdlib>
#include <vector>

namespace redko
{
  using point_t = std::pair< double, double >;
  using point_it = std::vector< point_t >::iterator;
  using size_it = std::vector< size_t >::iterator;

  bool isPointInCircle(point_t p, double radius);
  void fillWithRandomPoints(double radius, size_t tries, int seed, std::vector< point_t > & dest);
  void countPointsInCircle(double radius, point_it begin, size_t numOfPoints, size_it dest);
  double calculateCircleArea(double radius, size_t numOfThreads, size_t tries, int seed);
}

#endif
