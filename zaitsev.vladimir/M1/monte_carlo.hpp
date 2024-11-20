#ifndef MONTE_CARLO
#define MONTE_CARLO
#include <cstddef>
#include <vector>
#include "lrnd32.hpp"

namespace zaitsev
{
  double calc_area(size_t radius, size_t iterations, size_t threads, lrnd32 generator);
}
#endif
