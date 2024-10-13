#ifndef GETSQUARE_HPP
#define GETSQUARE_HPP
#include <vector>
#include <utility>
#include <cstddef>

namespace piyavkin
{
  void countPoints(const std::vector< std::pair< double, double > >& points, double r, size_t i, size_t amount, size_t& res);
  double getSquare(const std::vector< std::pair< double, double > >& points, size_t r, size_t countThreads);
}
#endif