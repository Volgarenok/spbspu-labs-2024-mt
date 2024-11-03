#include "compute_circle_area.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <thread>

kravchenko::Point generatePoint(std::uniform_real_distribution< double >& dist, std::minstd_rand& gen)
{
  return { dist(gen), dist(gen) };
}

kravchenko::DataPoint kravchenko::generateSamplePoints(size_t count, std::minstd_rand& generator, double radius)
{
  DataPoint points(count);
  std::uniform_real_distribution< double > dist(-radius, radius);
  auto bindedGenPoint = std::bind(generatePoint, std::ref(dist), std::ref(generator));
  std::generate(points.begin(), points.end(), bindedGenPoint);
  return points;
}

bool pointPred(const kravchenko::Point& p, double radius)
{
  return (p.first * p.first + p.second * p.second) <= radius * radius;
}

void checkPoints(kravchenko::DataPointConstIt begin, kravchenko::DataPointConstIt end, double radius, kravchenko::DataHitIt res)
{
  *res = std::count_if(begin, end, std::bind(pointPred, std::placeholders::_1, radius));
}

double kravchenko::computeCircleArea(const DataPoint& points, double radius, size_t threadsCount)
{
  std::vector< std::thread > threads;
  threads.reserve(threadsCount - 1);

  DataHit hits(threadsCount, 0);
  size_t perThread = points.size() / threadsCount;
  size_t lastThread = perThread + points.size() % threadsCount;

  auto begin = points.begin();
  for (size_t i = 0; i < threadsCount - 1; ++i)
  {
    auto end = begin + perThread;
    threads.emplace_back(checkPoints, begin, end, radius, hits.begin() + i);
    begin = end;
  }
  checkPoints(begin, begin + lastThread, radius, hits.end() - 1);

  for (auto&& thread : threads)
  {
    thread.join();
  }

  double ratio = std::accumulate(hits.cbegin(), hits.cend(), 0ull) / static_cast< double >(points.size());
  return ratio * 4.0 * radius * radius;
}
