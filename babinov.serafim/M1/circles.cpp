#include "circles.hpp"

std::istream& babinov::operator>>(std::istream& in, CircleData& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int radius = 0;
  int nThreads = 0;
  in >> radius >> nThreads;
  if (in)
  {
    data.radius = radius;
    data.nThreads = nThreads;
  }
  return in;
}
