#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include <istream>
#include <utility>
#include "base-types.hpp"

namespace piyavkin
{
  class Circle
  {
  public:
    Circle();
    Circle(const point_t& c, double r);
    rectangle_t getFrame() const;
    std::string getStr() const;
    bool isInside(const std::pair< double, double >& p) const;
  private:
    point_t center_;
    double radius_;
    friend std::ostream& operator<<(std::ostream& out, const Circle& c);
  };
  std::istream& operator>>(std::istream& in, Circle& c);
  std::ostream& operator<<(std::ostream& out, const Circle& c);
}
#endif