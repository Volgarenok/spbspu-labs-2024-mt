#include "CircleInput.hpp"
#include <istream>
#include "SizeType.hpp"

std::istream& novikov::operator>>(std::istream& in, CircleInput& circle)
{
  std::istream::sentry sentry(in);

  if (!sentry)
  {
    return in;
  }

  SizeType input_radius = {0};
  SizeType input_thread_count = {0};

  in >> input_radius >> input_thread_count;

  if (!in)
  {
    return in;
  }

  if (input_radius.size < 1 || input_thread_count.size < 1)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  circle.radius = input_radius.size;
  circle.thread_count = input_thread_count.size;

  return in;
}
