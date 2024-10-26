#include "calculateSquare.hpp"

#include <future>
#include <random>
#include <vector>
#include <cmath>

size_t countPartialPoints(size_t radius, size_t iterations, size_t seed)
{
  std::mt19937_64 generator(seed);
  std::uniform_real_distribution<> randUniform(0, radius);
  size_t points = 0;
  for (size_t i = 0; i < iterations; i++)
  {
    double x = randUniform(generator);
    double y = randUniform(generator);
    x -= radius;
    y -= radius;
    if (std::hypot(x, y) <= radius)
    {
      points++;
    }
  }
  return points;
}

double zhalilov::calcCircleSquare(size_t radius, size_t threads, size_t iterations, size_t startSeed)
{
  if (!threads || !iterations || !radius)
  {
    return 0.0;
  }

  std::vector< size_t > seeds(threads);
  std::mt19937_64 seedsGenerator(startSeed);
  for (auto&& seed : seeds)
  {
    seed = seedsGenerator();
  }

  std::vector< std::future< size_t > > futures;
  size_t pointsPerThread = iterations / threads;
  for (size_t i = 0; i < threads - 1; i++)
  {
    futures.emplace_back(std::async(countPartialPoints, radius, pointsPerThread, seeds[i]));
  }

  size_t remainedPoints = iterations % threads + pointsPerThread;
  std::future< size_t > remainedPointsFuture = std::async(countPartialPoints, radius, remainedPoints, seeds.back());
  size_t inCirclePoints = remainedPointsFuture.get();
  for (auto&& ftr : futures)
  {
    inCirclePoints += ftr.get();
  }
  double amountOfPoints = inCirclePoints / static_cast< double >(iterations);
  return 4.0 * radius * radius * amountOfPoints;
}
