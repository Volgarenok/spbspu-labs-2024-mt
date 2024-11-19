#include "Circle.hpp"
#include <istream>
#include <ostream>
#include "SizeType.hpp"

std::istream& novikov::operator>>(std::istream& in, Circle& circle)
{
  std::istream::sentry sentry(in);

  if (!sentry)
  {
    return in;
  }

  SizeType radius;
  Point center;

  in >> radius >> center;

  if (!in)
  {
    return in;
  }

  circle = {radius.size, center};
  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const Circle& circle)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
  {
    return out;
  }

  out << circle.radius << " " << circle.center;
  return out;
}
