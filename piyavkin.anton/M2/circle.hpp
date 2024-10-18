#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include <istream>
#include <ostream>
#include "base-types.hpp"

namespace piyavkin
{
  class Circle
  {
  public:
    Circle();
    Circle(const point_t& c, double r);
    rectangle_t getFrame() const;
  private:
    point_t center_;
    double radius_;
    friend std::ostream& operator<<(std::ostream& out, const Circle& c);
  };
  std::istream& operator>>(std::istream& in, Circle& c);
  std::ostream& operator<<(std::ostream& out, const Circle& c);
}
#endif