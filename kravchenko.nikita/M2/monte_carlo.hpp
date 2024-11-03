#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include <algorithm>
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

  template < class CircleDataIt >
  Frame getFrameSet(CircleDataIt begin, CircleDataIt end);

  PointDData generatePoints(size_t count, GeneratorT& gen, const Frame& frame);
  double computeArea(const PointDData& points, const CircleData& circles, const Frame& frame, size_t threadsCount);

  namespace pred
  {
    struct FramePred
    {
      FramePred(const Circle& c);
      void operator()(const Circle& c);
      Frame frame;
    };
  }
}

template < class CircleDataIt >
kravchenko::Frame kravchenko::getFrameSet(CircleDataIt begin, CircleDataIt end)
{
  pred::FramePred pred(*(begin++));
  std::for_each(begin, end, std::ref(pred));
  return pred.frame;
}

#endif
