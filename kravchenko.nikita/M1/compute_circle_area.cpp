#include "compute_circle_area.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <thread>
#include <vector>

namespace kravchenko
{
  using Point = std::pair< double, double >;
  using DataPoint = std::vector< Point >;
  using DataHit = std::vector< size_t >;
  using DataHitIt = DataHit::iterator;
}

kravchenko::Point generatePoint(std::uniform_real_distribution< double > dist, std::minstd_rand& gen)
{
  return { dist(gen), dist(gen) };
}

bool isPointInbound(const kravchenko::Point& p, double radius)
{
  return (p.first * p.first + p.second * p.second) <= radius * radius;
}

void checkPoints(kravchenko::DataPoint points, std::function< bool(const kravchenko::Point&) > pred, kravchenko::DataHitIt res)
{
  *res = std::count_if(points.begin(), points.end(), pred);
}

double kravchenko::computeCircleArea(size_t tries, std::minstd_rand& generator, double radius, size_t threadsCount)
{
  std::vector< std::thread > threads;
  threads.reserve(threadsCount - 1);

  DataHit hits(threadsCount, 0);
  size_t perThread = tries / threadsCount;
  size_t lastThread = perThread + tries % threadsCount;

  std::uniform_real_distribution< double > distribution(-radius, radius);
  auto genBoundPoint = std::bind(generatePoint, std::ref(distribution), std::ref(generator));
  std::function< bool(const Point&) > pointPred = std::bind(isPointInbound, std::placeholders::_1, radius);

  size_t i = 0;
  for (; i < threadsCount - 1; ++i)
  {
    DataPoint perThreadPoints(perThread);
    std::generate(perThreadPoints.begin(), perThreadPoints.end(), genBoundPoint);
    threads.emplace_back(checkPoints, std::move(perThreadPoints), pointPred, hits.begin() + i);
  }
  DataPoint lastThreadPoints(lastThread);
  std::generate(lastThreadPoints.begin(), lastThreadPoints.end(), genBoundPoint);
  checkPoints(lastThreadPoints, pointPred, hits.begin() + i);

  for (auto&& thread : threads)
  {
    thread.join();
  }

  double ratio = std::accumulate(hits.cbegin(), hits.cend(), 0ull) / static_cast< double >(tries);
  return ratio * 4.0 * radius * radius;
}