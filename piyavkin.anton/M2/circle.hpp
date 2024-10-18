#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include <string>
#include "point.hpp"

class Circle
{
public:
  Circle(const std::string& name, const point_t& c, size_t r);
// private:
  std::string name_;
  point_t center_;
  size_t radius_;
};
#endif