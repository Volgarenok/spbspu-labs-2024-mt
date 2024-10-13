#ifndef GETSQUARE_HPP
#define GETSQUARE_HPP
#include <vector>
#include <utility>
#include <cstddef>

namespace piyavkin
{
  double getSquare(const std::vector< std::pair< double, double > >& points, size_t r, size_t countThreads);
}
#endif