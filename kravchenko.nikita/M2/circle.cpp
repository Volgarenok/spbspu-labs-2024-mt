#include "circle.hpp"
#include <exception>

kravchenko::Circle::Circle():
  radius_(1),
  center_({ 0, 0 })
{}

kravchenko::Circle::Circle(int radius, int x, int y):
  center_({ x, y })
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid circle radius");
  }
  radius_ = radius;
}

int kravchenko::Circle::getRadius()
{
  return radius_;
}

const kravchenko::Point& kravchenko::Circle::getCenter()
{
  return center_;
}
