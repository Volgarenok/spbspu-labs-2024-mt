#ifndef GETSQUARE_HPP
#define GETSQUARE_HPP
#include <vector>
#include <utility>
#include <cstddef>

namespace piyavkin
{
  using data_t = std::vector< std::pair< double, double > >;
  void countPoints(const data_t& points, double r, size_t i, size_t amount, size_t& res);
  double getSquare(const data_t& points, size_t r, size_t countThreads);
}
#endif
