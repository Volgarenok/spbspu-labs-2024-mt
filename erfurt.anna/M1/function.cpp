#include "function.hpp"
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

size_t erfurt::countPointsInCircul(c_it_t begin, c_it_t end)
{
  return std::accumulate(begin, end, 0);
}

double erfurt::getSquare(size_t seed, size_t numOfTests, double radius, size_t countOfThreads)
{
  size_t threads = std::min(static_cast<size_t>(std::thread::hardware_concurrency()) - 1, countOfThreads);
  std::vector< std::thread > ths;
  ths.reserve(threads - 1);
  std::vector< size_t > results(threads, 0);
  size_t per_th = numOfTests / threads;
  size_t last_th = per_th + numOfTests % threads;
  size_t i = 0;
  for (; i < threads - 1; ++i)
  {
    ths.emplace_back(countPointsInCircul_th, seed, per_th, radius, results.begin() + i);
    seed++;
  }
  countPointsInCircul_th(seed, last_th, radius, results.begin() + i);
  for (auto&& th : ths)
  {
    th.join();
  }
  size_t countPoints = countPointsInCircul(results.cbegin(), results.cend());
  return (countPoints * 4 * radius * radius) / numOfTests;
}