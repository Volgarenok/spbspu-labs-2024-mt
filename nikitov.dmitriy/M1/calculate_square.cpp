#include "calculate_square.hpp"
#include <algorithm>
#include <numeric>
#include <thread>
#include <future>
#include <random>
#include <vector>

#include <iostream>

size_t countPart(size_t radius, size_t tries, typename std::vector< double >::const_iterator iterator)
{
  size_t count = 0;
  for (size_t i = 0; i != tries; ++i)
  {
    double x = *(iterator++);
    double y = *(iterator++);
    if (std::hypot(x, y) <= radius)
    {
      ++count;
    }
  }
  return count;
}

double nikitov::calculateSquare(size_t radius, size_t numberOfThreads, size_t seed, size_t tries)
{
  size_t threads = std::thread::hardware_concurrency();
  numberOfThreads = std::min(numberOfThreads, threads);

  std::vector< double > nums(tries * 2, 0.0);

  std::default_random_engine randomizer(seed);
  std::uniform_real_distribution< double > distribution(0.0, radius);

  for (size_t i = 0; i != tries * 2; ++i)
  {
    nums[i] = distribution(randomizer);
  }

  std::vector< std::future< size_t > > futures;
  futures.reserve(numberOfThreads - 1);
  std::vector< size_t > counts(numberOfThreads, 0);

  for (size_t i = 0; i != numberOfThreads - 1; ++i)
  {
    futures.emplace_back(std::async(countPart, radius, tries / numberOfThreads, nums.cbegin() + (tries * 2 / numberOfThreads * i)));
  }
  counts.back() = countPart(radius, tries / numberOfThreads + tries % numberOfThreads, nums.cbegin() + (tries * 2 / numberOfThreads * (numberOfThreads - 1)));

  std::transform(futures.begin(), futures.end(), counts.begin(),
    [](auto && future)
    {
      return future.get();
    });

  return 4.0 * std::pow(radius, 2) * std::accumulate(counts.cbegin(), counts.cend(), 0) / tries;
}

