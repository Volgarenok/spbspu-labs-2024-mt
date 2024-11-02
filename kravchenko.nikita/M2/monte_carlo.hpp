#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include <random>
#include <utility>
#include <vector>
#include "circle.hpp"

namespace kravchenko
{
  using PointD = std::pair< double, double >;
  using PointDData = std::vector< PointD >;
  using CircleData = std::vector< Circle >;
  using GeneratorT = std::minstd_rand;

  PointDData generatePoints(size_t count, GeneratorT& gen, const Frame& area);
  double computeArea(const PointDData& points, const CircleData& circles, const Frame& frame, size_t threadsCount);
}

#endif