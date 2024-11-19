#include "Frame.hpp"
#include <ostream>

std::ostream& novikov::operator<<(std::ostream& out, const Frame& frame)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
  {
    return out;
  }

  out << frame.left_down << " " << frame.up_right;
  return out;
}
