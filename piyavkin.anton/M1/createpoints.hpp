#ifndef CREATEPOINTS_HPP
#define CREATEPOINTS_HPP
#include <random>
#include <vector>
#include <utility>

namespace piyavkin
{
  using data_t = std::vector< std::pair< double, double > >;
  void createPoints(std::minstd_rand& gen, data_t& points, double r, size_t size);
}
#endif
