#ifndef CALCULATE_CIRCLE_SQUARE_HPP
#define CALCULATE_CIRCLE_SQUARE_HPP

#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include "generate_random_point.hpp"

namespace erohin
{
  void countRandomPoints(size_t number, size_t radius, std::minstd_rand & generator, size_t & result);
  double calculateCircleSquare(size_t radius, size_t threads_number, size_t tries_number, size_t seed);
}

#endif
