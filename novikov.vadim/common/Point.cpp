#include "Point.hpp"
#include <istream>
#include <ostream>

std::istream& novikov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);

  if (!sentry)
  {
    return in;
  }

  ptrdiff_t x;
  ptrdiff_t y;

  in >> x >> y;

  if (!in)
  {
    return in;
  }

  point = {x, y};
  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
  {
    return out;
  }

  out << "(" << point.x << " " << point.y << ")";
  return out;
}
