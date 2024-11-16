#ifndef SETPROCESSING_HPP
#define SETPROCESSING_HPP
#include "circle.hpp"
#include "areaProcessing.hpp"
#include <thread>

namespace redko
{
  std::pair< Point, Point > getSetFrame(set_it setIt);
  bool isPointInSet(Point p, set_it set);
  void fillWithRandomRectPoints(set_it set, size_t tries, int seed, std::vector< Point > & dest);
  void countPointsInSet(set_it set, point_it begin, size_t numOfPoints, size_it dest);
  void calculateArea(std::vector< std::thread > & threads, set_it setIt, size_t numOfThreads, size_t tries, int seed, double & result, bool & finished);
}

#endif
