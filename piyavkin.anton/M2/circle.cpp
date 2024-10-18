#include "circle.hpp"

piyavkin::Circle::Circle():
  Circle({0,0}, 0)
{}

piyavkin::Circle::Circle(const point_t& c, double r):
  center_(c),
  radius_(r)
{}

std::istream& piyavkin::operator>>(std::istream& in, Circle& c)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double x = 0;
  double y = 0;
  double r = 0;
  in >> x >> y >> r;
  if (in)
  {
    Circle temp({x, y}, r);
    c = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
