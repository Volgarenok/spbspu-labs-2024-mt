#include "Function.hpp"
#include <random>
#include <algorithm>
#include <numeric>
#include <thread>
#include <functional>

void erfurt::countPointsInCircul_th(size_t seed, size_t numOfTests, double radius, it_t res)
{
  size_t countPoints = 0;
  std::mt19937 generator(seed);
  std::uniform_real_distribution<double> distribution(-radius, radius);
  for (size_t i = 0; i < numOfTests; ++i)
  {
    double x = distribution(generator);
    double y = distribution(generator);
    if (x * x + y * y <= radius * radius)
    {
      ++countPoints;
    }

  }
  *res = countPoints;
}