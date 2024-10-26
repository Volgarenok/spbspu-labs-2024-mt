#include "areaProcessing.hpp"
#include <functional>
#include <random>
#include <thread>

bool redko::isPointInCircle(point_t p, double radius)
{
  return pow(p.first, 2) + pow(p.second, 2) <= pow(radius, 2);
}

void redko::countPointsInCircle(double radius, point_it begin, size_t numOfPoints, size_it dest)
{
  using namespace std::placeholders;
  *dest = std::count_if(begin, begin + numOfPoints, std::bind(isPointInCircle, _1, radius));
}

double redko::calculateCircleArea(double radius, size_t numOfThreads, size_t tries, int seed)
{
  std::default_random_engine eng(seed);
  std::uniform_real_distribution< double > doubleDist(-radius, radius);

  std::vector< point_t > points;
  for (int i = 0; i < tries; ++i)
  {
    double x = doubleDist(eng);
    double y = doubleDist(eng);
    points.push_back({ x, y });
  }
  
  std::vector< std::thread > threads;
  threads.reserve(numOfThreads - 1);
  size_t trPerTh = tries / numOfThreads;
  size_t lastTr = trPerTh + tries % numOfThreads;

  std::vector< size_t > counts(numOfThreads);
  point_it currP = points.begin();
  size_it currCnt = counts.begin();
  for (int i = 0; i < numOfThreads - 1; ++i)
  {
    threads.emplace_back(redko::countPointsInCircle, radius, currP, trPerTh, currCnt);
    currP += trPerTh;
    ++currCnt;
  }
  threads.emplace_back(redko::countPointsInCircle, radius, currP, lastTr, currCnt);

  for (auto && th : threads)
  {
    th.join();
  }

  size_t pointsInCircle = std::accumulate(counts.cbegin(), counts.cend(), 0);
  double frameArea = pow(2 * radius, 2);
  double circleArea = frameArea * (static_cast< double >(pointsInCircle) / static_cast< double >(tries));
  return circleArea;
}
