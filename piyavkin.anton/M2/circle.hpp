#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include <istream>
#include "base-types.hpp"

namespace piyavkin
{
  class Circle
  {
  public:
    Circle();
    Circle(const point_t& c, double r);
  // private:
    point_t center_;
    double radius_;
  };
  std::istream& operator>>(std::istream& in, Circle& c);
}
#endif