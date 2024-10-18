#include "calculate_square.hpp"
#include <algorithm>
#include <numeric>
#include <thread>
#include <future>
#include <random>
#include <vector>

size_t countPart(int radius, int seed, int tries, size_t id)
{
  std::default_random_engine randomizer(seed);
  std::uniform_real_distribution< double > distribution(- radius, radius);
  size_t count = 0;
  for (int i = 0; i != tries; ++i)
  {
    for (size_t j = 0; j != id * 2; ++j)
    {
      distribution(randomizer);
    }
    double x = distribution(randomizer);
    double y = distribution(randomizer);
    if (x * x + y * y <= radius * radius)
    {
      ++count;
    }
  }
  return count;
}

double nikitov::calculateSquare(int radius, int numberOfThreads, int seed, int tries)
{
  std::vector< std::future< size_t > > futures;
  futures.reserve(numberOfThreads);
  std::vector< size_t > counts(numberOfThreads, 0);
  for (int i = 0; i != numberOfThreads; ++i)
  {
    futures.emplace_back(std::async(countPart, radius, seed, tries / numberOfThreads, i));
  }

  std::transform(futures.begin(), futures.end(), counts.begin(),
  [](auto && future)
  {
    return future.get();
  });

  return 4.0 * radius * radius * std::accumulate(counts.cbegin(), counts.cend(), 0) / tries;
}