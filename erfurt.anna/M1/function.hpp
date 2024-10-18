#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <vector>
#include <iterator>

namespace erfurt
{
  using data_t = std::vector< size_t >;
  using it_t = data_t::iterator;
  using c_it_t = data_t::const_iterator;
  
  void countPointsInCircul_th(size_t seed, size_t numOfTests, double radius, it_t res);
  size_t countPointsInCircul(c_it_t begin, c_it_t end);
  double getSquare(size_t seed, size_t numOfTests, double radius, size_t countOfThreads);
}

#endif
