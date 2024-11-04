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

int kravchenko::Circle::getRadius() const
{
  return radius_;
}

const kravchenko::Point& kravchenko::Circle::getCenter() const
{
  return center_;
}

kravchenko::Frame kravchenko::Circle::getFrame() const
{
  return { { center_.x - radius_, center_.y - radius_ }, { center_.x + radius_, center_.y + radius_ } };
}

std::ostream& kravchenko::operator<<(std::ostream& out, const Point& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << p.x;
  out << ' ' << p.y << ')';
  return out;
}

std::ostream& kravchenko::operator<<(std::ostream& out, const Frame& f)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << f.leftBottom << ' ' << f.rightTop;
}

std::istream& kravchenko::operator>>(std::istream& in, Circle& c)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int radius = 0;
  int x = 0;
  int y = 0;
  in >> radius >> x >> y;
  if (in)
  {
    try
    {
      c = Circle(radius, x, y);
    }
    catch (const std::invalid_argument& e)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::ostream& kravchenko::operator<<(std::ostream& out, const Circle& c)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << c.getRadius() << ' ' << c.getCenter();
  return out;
}
