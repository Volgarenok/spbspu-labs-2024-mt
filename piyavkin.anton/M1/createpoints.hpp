#ifndef CREATEPOINTS_HPP
#define CREATEPOINTS_HPP
#include <random>
#include <vector>
#include <utility>

namespace piyavkin
{
  void createPoints(std::minstd_rand& gen, std::vector< std::pair< double, double > >& points, double r, size_t size);
}
#endif