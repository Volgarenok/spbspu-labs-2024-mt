#ifndef GET_AREA_HPP
#define GET_AREA_HPP

#include <vector>
#include <utility>
#include <random>

namespace novokhatskiy
{
  using Point = std::pair< double, double >;
  using vec_p = std::vector< Point >;
  using const_it_p = vec_p::const_iterator;
  using val_it = std::vector< size_t >::iterator;

  Point createPoint(size_t r, std::minstd_rand& randomDevice);
  vec_p generateValues(size_t tries, size_t r, std::minstd_rand& randomDevice);
  bool isPointInsideCircle(const Point& p, size_t r);
  void checkInsidePoints(const_it_p begin, const_it_p end, size_t r, val_it res);
  double processMK(size_t r, size_t threads, size_t tries, std::minstd_rand& randomDevice);
}

#endif
