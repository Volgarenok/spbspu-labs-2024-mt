#include "CircleInput.hpp"
#include <istream>

std::istream& novikov::operator>>(std::istream& in, CircleInput& circle)
{
  std::istream::sentry sentry(in);

  if (!sentry)
  {
    return in;
  }

  ptrdiff_t input_radius = 0;
  ptrdiff_t input_thread_count = 0;

  in >> input_radius >> input_thread_count;

  if (!in)
  {
    return in;
  }

  if (input_radius < 0 || input_thread_count < 1)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  circle.radius = input_radius;
  circle.thread_count = input_thread_count;

  return in;
}
