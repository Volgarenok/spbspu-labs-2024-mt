#ifndef GETSQUARE_HPP
#define GETSQUARE_HPP
#include <vector>
#include <utility>
#include "base-types.hpp"
#include "set.hpp"

namespace piyavkin
{
  using data_t = std::vector< std::pair< double, double > >;
  void countPoints(const data_t& points, const Set& set, size_t i, size_t amount, size_t& res);
  double getSquare(const data_t& points, const Set& set, const rectangle_t& r, size_t countThreads);
}
#endif