#include "generator.hpp"

babinov::Generator::Generator(size_t seed, double from, double to):
  dist(from, to),
  gen(seed)
{}

double babinov::Generator::next()
{
  return dist(gen);
}
