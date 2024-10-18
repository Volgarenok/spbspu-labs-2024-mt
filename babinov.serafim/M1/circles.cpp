#include "circles.hpp"
#include <algorithm>
#include <cmath>
#include <future>
#include <random>
#include <vector>

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

double getSquare(babinov::CircleData data, size_t seed, size_t tries)
{
  std::vector< std::future< size_t > > futures;
  futures.reserve(data.nThreads - 1);
  std::vector< size_t > results(data.nThreads, 0);

  size_t ts = tries;
  size_t triesForOne = tries / data.nThreads;
  for (size_t i = 0; i < data.nThreads - 1; ++i, ts -= triesForOne)
  {
    futures.emplace_back(std::async(calculatePoints, seed, triesForOne, tries - ts, data.radius));
  }
  results.back() = calculatePoints(seed, ts, tries - ts, data.radius);
  std::transform(futures.begin(), futures.end(), results.begin(),
   [](auto && ft)
   {
     return ft.get();
   });
  return std::accumulate(results.cbegin(), results.cend(), 0.0) / tries * 4 * data.radius * data.radius;
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
