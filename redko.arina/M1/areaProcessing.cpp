#include "areaProcessing.hpp"
#include <functional>
#include <random>
#include <thread>

bool redko::isPointInCircle(Point p, int radius)
{
  return pow(p.x, 2) + pow(p.y, 2) <= pow(radius, 2);
}

void redko::fillWithRandomPoints(double radius, size_t tries, int seed, std::vector< Point > & dest)
{
  std::default_random_engine eng(seed);
  std::uniform_real_distribution< double > doubleDist(-radius, radius);

  for (size_t i = 0; i < tries; ++i)
  {
    double x = doubleDist(eng);
    double y = doubleDist(eng);
    dest.push_back({ x, y });
  }
}

void redko::countPointsInCircle(int radius, point_it begin, size_t numOfPoints, size_it dest)
{
  using namespace std::placeholders;
  *dest = std::count_if(begin, begin + numOfPoints, std::bind(isPointInCircle, _1, radius));
}

double redko::calculateCircleArea(int radius, size_t numOfThreads, size_t tries, int seed)
{
  std::vector< std::thread > threads;
  threads.reserve(numOfThreads - 1);
  size_t trPerTh = tries / numOfThreads;
  size_t lastTr = trPerTh + tries % numOfThreads;

  std::vector< Point > points;
  points.reserve(tries);
  fillWithRandomPoints(radius, tries, seed, points);
  point_it currP = points.begin();
  std::vector< size_t > counts(numOfThreads);
  size_it currCnt = counts.begin();
  for (int i = 0; i < numOfThreads - 1; ++i)
  {
    threads.emplace_back(countPointsInCircle, radius, currP, trPerTh, currCnt);
    currP += trPerTh;
    ++currCnt;
  }
  threads.emplace_back(countPointsInCircle, radius, currP, lastTr, currCnt);

  for (auto && th : threads)
  {
    th.join();
  }

  size_t pointsInCircle = std::accumulate(counts.cbegin(), counts.cend(), 0);
  int frameArea = pow(2 * radius, 2);
  double circleArea = static_cast< double >(frameArea) * (static_cast< double >(pointsInCircle) / static_cast< double >(tries));
  return circleArea;
}
