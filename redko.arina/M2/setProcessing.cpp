#include "setProcessing.hpp"
#include <functional>
#include <algorithm>
#include <random>
#include <numeric>

std::pair< redko::Point, redko::Point > redko::getSetFrame(set_it setIt)
{
  std::set< double > leftX;
  std::set< double > leftY;
  std::set< double > rightX;
  std::set< double > rightY;
  std::transform(setIt->second.begin(), setIt->second.end(), std::inserter(leftX, leftX.begin()), [](Circle c) {return c.center.x - c.radius; });
  std::transform(setIt->second.begin(), setIt->second.end(), std::inserter(leftY, leftY.begin()), [](Circle c) {return c.center.y - c.radius; });
  std::transform(setIt->second.begin(), setIt->second.end(), std::inserter(rightX, rightX.begin()), [](Circle c) {return c.center.x + c.radius; });
  std::transform(setIt->second.begin(), setIt->second.end(), std::inserter(rightY, rightY.begin()), [](Circle c) {return c.center.y + c.radius; });
  double minX = *std::min_element(leftX.begin(), leftX.end());
  double minY = *std::min_element(leftY.begin(), leftY.end());
  Point left = { minX, minY };
  double maxX = *std::max_element(rightX.begin(), rightX.end());
  double maxY = *std::max_element(rightY.begin(), rightY.end());
  Point right = { maxX, maxY };
  return { left, right };
}

bool redko::isPointInSet(Point p, set_it set)
{
  return std::any_of(set->second.begin(), set->second.end(), [p](const Circle & c) {
    return pow(p.x - c.center.x, 2) + pow(p.y - c.center.y, 2) <= pow(c.radius, 2); 
    });
}

void redko::fillWithRandomRectPoints(set_it set, size_t tries, int seed, std::vector< Point > & dest)
{
  std::pair< Point, Point > frame = getSetFrame(set);
  std::default_random_engine eng(seed);
  std::uniform_real_distribution< double > distX(frame.first.x, frame.second.x);
  std::uniform_real_distribution< double > distY(frame.first.y, frame.second.y);
  for (size_t i = 0; i < tries; ++i)
  {
    dest.push_back({ distX(eng), distY(eng) });
  }
}

void redko::countPointsInSet(set_it set, point_it begin, size_t numOfPoints, size_it dest)
{
  using namespace std::placeholders;
  *dest = std::count_if(begin, begin + numOfPoints, std::bind(isPointInSet, _1, set));
}

void redko::calculateArea(std::vector< std::thread > & threads, set_it setIt, size_t numOfThreads, size_t tries, int seed, double & result, bool & finished)
{
  std::vector< Point > points;
  points.reserve(tries);
  fillWithRandomRectPoints(setIt, tries, seed, points);
  point_it currP = points.begin();
  std::vector< size_t > counts(numOfThreads);
  size_it currCnt = counts.begin();
  if (numOfThreads == 1)
  {
    countPointsInSet(setIt, currP, tries, currCnt);
  }
  else
  {
    size_t trPerTh = tries / (numOfThreads);
    size_t lastTr = trPerTh + tries % (numOfThreads);
    for (size_t i = 0; i < numOfThreads - 1; ++i)
    {
      threads.emplace_back(countPointsInSet, setIt, currP, trPerTh, currCnt);
      currP += trPerTh;
      ++currCnt;
    }
    countPointsInSet(setIt, currP, lastTr, currCnt);
    for (auto th = threads.begin() + 1; th != threads.end(); ++th)
    {
      if (th->joinable()) th->join();
    }
  }
  
  size_t pointsInSet = std::accumulate(counts.cbegin(), counts.cend(), 0);
  std::pair< Point, Point > frame = getSetFrame(setIt);
  int frameArea = (frame.second.x - frame.first.x) * (frame.second.y - frame.first.y);
  double setArea = static_cast< double >(frameArea) * (static_cast< double >(pointsInSet) / static_cast< double >(tries));
  result = setArea;
  finished = true;
}
