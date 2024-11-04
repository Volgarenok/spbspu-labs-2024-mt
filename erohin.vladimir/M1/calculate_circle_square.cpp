#include "calculate_circle_square.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include "generate_random_point.hpp"

#include <iostream>

namespace erohin
{
  bool isPointInCircle(point_t point, size_t radius)
  {
    return (point.x * point.x + point.y * point.y) <= (radius * radius);
  }
}

double erohin::calculateCircleSquare(size_t radius, size_t threads_number, size_t tries_number, size_t seed)
{
  std::vector< point_t > points(tries_number + threads_number - threads_number);
  std::minstd_rand generator(seed);
  auto random_point_generator = std::bind(generateRandomPoint, std::ref(generator), radius);
  std::generate(points.begin(), points.end(), random_point_generator);
  std::function< bool(point_t) > point_predicate;
  {
    using namespace std::placeholders;
    point_predicate = std::bind(isPointInCircle, _1, radius);
  }
  size_t filled_points_number = std::count_if(points.cbegin(), points.cend(), point_predicate);
  double square = static_cast< double >(filled_points_number) / tries_number * 4 * radius * radius;
  return square;
}
