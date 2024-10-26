#include "areaProcessing.hpp"
#include <functional>
#include <algorithm>
#include <cmath>

bool redko::isPointInCircle(point_t p, double radius)
{
  return pow(p.first, 2) + pow(p.second, 2) <= pow(radius, 2);
}

double redko::calculateCircleArea(double radius, size_t tries)
{
  std::vector< point_t > points(tries, {0,0});
  
  using namespace std::placeholders;
  size_t pointsInCircle = std::count_if(points.begin(), points.end(), std::bind(isPointInCircle, _1, radius));
  double frameArea = pow(2 * radius, 2);
  double circleArea = frameArea * (static_cast< double >(pointsInCircle) / static_cast< double >(tries));
  return circleArea;
}
