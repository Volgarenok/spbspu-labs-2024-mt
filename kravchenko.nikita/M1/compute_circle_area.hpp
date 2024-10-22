#ifndef COMPUTE_CIRCLE_AREA
#define COMPUTE_CIRCLE_AREA

#include <random>
#include <utility>
#include <vector>

namespace kravchenko
{
  using Point = std::pair< double, double >;
  using DataPoint = std::vector< Point >;
  using DataPointConstIt = DataPoint::const_iterator;
  using DataHit = std::vector< size_t >;
  using DataHitIt = DataHit::iterator;
  DataPoint generateSamplePoints(size_t count, std::minstd_rand& generator, double radius);
  double computeCircleArea(const DataPoint& points, double radius, size_t threadsCount);
}

#endif
