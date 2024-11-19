#ifndef AREA_COMPUTER_HPP
#define AREA_COMPUTER_HPP

#include <vector>
#include <utility>
#include <random>
#include "CircleInput.hpp"
#include "CircleOutput.hpp"

namespace novikov
{
  class AreaComputer
  {
  public:

    AreaComputer(size_t tries, size_t seed);
    CircleOutput operator()(const CircleInput& circle);

  private:

    using point_t = std::pair< double, double >;
    using it_t = std::vector< point_t >::iterator;

    std::vector< size_t > hits_;
    size_t tries_;
    size_t seed_;

    point_t generatePoint(std::mt19937& generator, double radius, size_t hits_index);
    void generatePoints(it_t begin, it_t end, double radius, size_t hits_index);
  };
}

#endif
