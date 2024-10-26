#include "calculateSquare.hpp"

#include <future>
#include <random>
#include <vector>

size_t countPartialPoints(size_t radius, size_t iterations, size_t seed)
{
  std::mt19937_64 generator(seed);
  std::uniform_real_distribution<> randUniform(-radius, radius);
  size_t points = 0;
  for (size_t i = 0; i < iterations; i++)
  {
    double x = randUniform(generator);
    double y = randUniform(generator);
    if (x * x + y * y <= radius * radius)
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

  std::future< size_t > remainedPoints = std::async(countPartialPoints, radius, iterations % threads, seeds.back());
  size_t inCirclePoints = remainedPoints.get();
  for (auto&& ftr : futures)
  {
    inCirclePoints += ftr.get();
  }
  return inCirclePoints / static_cast< double >(iterations);
}
