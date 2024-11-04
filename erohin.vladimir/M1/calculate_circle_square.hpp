#ifndef CALCULATE_CIRCLE_SQUARE_HPP
#define CALCULATE_CIRCLE_SQUARE_HPP

#include <vector>
#include "generate_random_point.hpp"

namespace erohin
{
  using point_array_t = std::vector< point_t >;

  void generatePoints(point_array_t & points, size_t limit, size_t seed);
  void countPoints(const point_array_t & points, size_t index, size_t number, size_t radius, size_t & result);
  double calculateCircleSquare(size_t radius, size_t threads_number, size_t tries_number, size_t seed);
}

#endif
