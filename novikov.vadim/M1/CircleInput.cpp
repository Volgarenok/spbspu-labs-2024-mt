#include "CircleInput.hpp"
#include <istream>
#include <stdexcept>

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

  if (input_radius < 0 || input_thread_count < 1)
  {
    throw std::invalid_argument("Некорректный ввод!");
  }

  circle.radius = input_radius;
  circle.thread_count = input_thread_count;

  return in;
}
