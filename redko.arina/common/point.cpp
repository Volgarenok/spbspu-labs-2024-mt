#include "point.hpp"

std::ostream & redko::operator<<(std::ostream & out, const Point & point)
{
  out << '(' << point.x << ' ' << point.y << ')';
  return out;
}
