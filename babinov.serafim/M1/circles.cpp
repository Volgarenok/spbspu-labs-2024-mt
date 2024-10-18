#include "circles.hpp"
#include <cmath>
#include <random>
#include "randomizer.hpp"

size_t calculatePoints(size_t seed, size_t tries, size_t skips, size_t radius)
{
  size_t inTarget = 0;
  babinov::Randomizer rand(seed, 0, radius);
  rand.skip(skips);
  for (size_t i = 0; i < tries; ++i)
  {
    double x = rand.next();
    double y = rand.next();
    if (std::hypot(x, y) <= radius)
    {
      ++inTarget;
    }
  }
  return inTarget;
}

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
  if (!in)
  {
    return in;
  }
  if ((radius > 0) && (nThreads > 0))
  {
    data.radius = radius;
    data.nThreads = nThreads;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
