#include "areaProcessing.hpp"
#include <functional>
#include <algorithm>
#include <cmath>
#include <random>

bool redko::isPointInCircle(point_t p, double radius)
{
  return pow(p.first, 2) + pow(p.second, 2) <= pow(radius, 2);
}

double redko::calculateCircleArea(double radius, size_t tries, int seed)
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
  
  using namespace std::placeholders;
  size_t pointsInCircle = std::count_if(points.begin(), points.end(), std::bind(isPointInCircle, _1, radius));
  double frameArea = pow(2 * radius, 2);
  double circleArea = frameArea * (static_cast< double >(pointsInCircle) / static_cast< double >(tries));
  return circleArea;
}
