#include "randomizer.hpp"

babinov::Randomizer::Randomizer(size_t seed, double from, double to):
  dist(from, to),
  gen(seed)
{}

double babinov::Randomizer::next()
{
  return dist(gen);
}

void babinov::Randomizer::skip(size_t number)
{
  for (size_t i = 0; i < number; ++i)
  {
    next();
  }
}
