#include "circle.hpp"

piyavkin::Circle::Circle():
  Circle({0, 0}, 0)
{}

piyavkin::Circle::Circle(const point_t& c, double r):
  center_(c),
  radius_(r)
{}

piyavkin::rectangle_t piyavkin::Circle::getFrame() const
{
  return {{center_.x - radius_, center_.y - radius_}, {center_.x + radius_, center_.y + radius_}};
}

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
  in >> r >> x >> y;
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

std::ostream& piyavkin::operator<<(std::ostream& out, const Circle& c)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << c.radius_ << ' ' << c.center_; 
  return out;
}
