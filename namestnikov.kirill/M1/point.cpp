#include "point.hpp"

namestnikov::Point::Point(double x, double y):
  x_(x),
  y_(y)
{}

double namestnikov::Point::getX() const
{
  return x_;
}

double namestnikov::Point::getY() const
{
  return y_;
}
