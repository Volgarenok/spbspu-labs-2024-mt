#include "calculate_square.hpp"
#include <cstdlib>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>
#include <random>

size_t countPart(int radius, int seed, int tries, size_t id)
{
  std::default_random_engine randomizer(seed);
  std::uniform_int_distribution< int > distribution(- radius, radius);
  size_t count = 0;
  for (int i = 0; i != tries; ++i)
  {
    for (size_t j = 0; j != id * 2; ++j)
    {
      distribution(randomizer);
    }
    int x = distribution(randomizer);
    int y = distribution(randomizer);
    if (x * x + y * y <= radius * radius)
    {
      ++count;
    }
  }
  return count;
}

double calculateSquare(int radius, int numberOfThreads, int seed, int tries)
{
  std::srand(seed);
  std::vector< std::future< size_t > > futures;
  futures.reserve(numberOfThreads);
  std::vector< size_t > squares(numberOfThreads, 0);
  for (int i = 0; i != numberOfThreads; ++i)
  {
    futures.emplace_back(std::async(calculateSquare, radius, seed, tries / numberOfThreads, i));
  }

  return 0.0;
}