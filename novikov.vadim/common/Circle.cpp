#include "Circle.hpp"
#include <istream>
#include "SizeType.hpp"

std::istream& novikov::operator>>(std::istream& in, Circle& circle)
{
  std::istream::sentry sentry(in);

  if (!sentry)
  {
    return in;
  }

  SizeType radius;
  ptrdiff_t x;
  ptrdiff_t y;

  in >> radius >> x >> y;

  if (!in)
  {
    return in;
  }

  circle.radius = radius.size;
  circle.x = x;
  circle.y = y;

  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const Circle& circle)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
  {
    return out;
  }

  out << circle.radius << " (" << circle.x << " " << circle.y << ")";
  return out;
}
