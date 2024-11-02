#include "monte_carlo.hpp"
#include <algorithm>
#include <functional>
#include <thread>

namespace kravchenko
{
  using HitData = std::vector< size_t >;
  using DisributionT = std::uniform_real_distribution< double >;
  PointD generatePoint(DisributionT& distX, DisributionT& distY, GeneratorT& gen);
  bool isPointInCircle(const PointD& p, const Circle& c);
  bool pointPred(const PointD& p, CircleData::const_iterator begin, CircleData::const_iterator end);
  void checkPoints(PointDData::const_iterator cbeginPoints, PointDData::const_iterator cendPoints,
                   CircleData::const_iterator cbeginCircles, CircleData::const_iterator cendCircles, HitData::iterator res);
}

kravchenko::PointD kravchenko::generatePoint(DisributionT& distX, DisributionT& distY, GeneratorT& gen)
{
  return { distX(gen), distY(gen) };
}

kravchenko::PointDData kravchenko::generatePoints(size_t count, GeneratorT& gen, const Frame& area)
{
  PointDData points(count);
  DisributionT distX(area.leftBottom.x, area.rightTop.x);
  DisributionT distY(area.leftBottom.y, area.rightTop.y);
  auto pointGen = std::bind(generatePoint, std::ref(distX), std::ref(distY), std::ref(gen));
  std::generate(points.begin(), points.end(), pointGen);
  return points;
}

bool kravchenko::isPointInCircle(const PointD& p, const Circle& c)
{
  double xSqr = (p.first - c.getCenter().x) * (p.first - c.getCenter().x);
  double ySqr = (p.second - c.getCenter().y) * (p.second - c.getCenter().y);
  double radiusSqr = c.getRadius() * c.getRadius();
  return (xSqr + ySqr) <= radiusSqr;
}

bool kravchenko::pointPred(const PointD& p, CircleData::const_iterator begin, CircleData::const_iterator end)
{
  using namespace std::placeholders;
  return std::any_of(begin, end, std::bind(isPointInCircle, std::cref(p), _1));
}

void kravchenko::checkPoints(PointDData::const_iterator cbeginPoints, PointDData::const_iterator cendPoints,
                             CircleData::const_iterator cbeginCircles, CircleData::const_iterator cendCircles,
                             HitData::iterator res)
{
  using namespace std::placeholders;
  *res = std::count_if(cbeginPoints, cendPoints, std::bind(pointPred, _1, cbeginCircles, cendCircles));
}

double kravchenko::computeArea(const PointDData& points, const CircleData& circles, const Frame& frame, size_t threadsCount)
{
  std::vector< std::thread > threads;
  threads.reserve(threadsCount - 1);

  HitData hits(threadsCount, 0);
  size_t perThread = points.size() / threadsCount;
  size_t lastThread = perThread + points.size() % threadsCount;

  auto begin = points.cbegin();
  for (size_t i = 0; i < threadsCount - 1; ++i)
  {
    auto end = begin + perThread;
    threads.emplace_back(checkPoints, begin, end, circles.cbegin(), circles.cend(), hits.begin() + i);
    begin = end;
  }
  checkPoints(begin, begin + lastThread, circles.cbegin(), circles.cend(), hits.end() - 1);

  for (auto&& thread : threads)
  {
    thread.join();
  }

  double ratio = std::accumulate(hits.cbegin(), hits.cend(), 0ull) / static_cast< double >(points.size());
  int area = (frame.rightTop.x - frame.leftBottom.x) * (frame.rightTop.y - frame.leftBottom.y);
  return ratio * area;
}
