#ifndef CALCULATE_SQUARE_HPP
#define CALCULATE_SQUARE_HPP

#include <cstddef>
#include <vector>
#include <random>
#include "point.hpp"

namespace namestnikov
{
  double getSquare(std::default_random_engine & gen, size_t numberOfTests, int radius, size_t threadsCount);
}

#endif 