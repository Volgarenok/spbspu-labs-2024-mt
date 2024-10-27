#include <cmath>
#include <random>
#include <thread>
#include <vector>
#include <iostream>
#include <future>
#include <algorithm>
#include <chrono>
#include <functional>
#include "calculate_square.hpp"

double getSquareLin(std::default_random_engine & gen, size_t numberOfTests, int radius)
{
  using namespace namestnikov;
  std::uniform_real_distribution< double > distribution(-radius, radius);
  int res = 0;
  for (size_t i = 0; i < numberOfTests; ++i)
  {
    double x = distribution(gen);
    double y = distribution(gen);
    //std::cout << x << " " << y;
    Point point(x, y);
    if (std::pow(point.getX(), 2) + std::pow(point.getY(), 2) <= std::pow(radius, 2))
    {
      ++res;
    }
  }
  return 4 * std::pow(radius, 2) * res / numberOfTests;
}

int main()
{
  using namespace namestnikov;
  size_t seed = 5;
  int radius = 2;
  size_t numberOfTests = 100000000;
  size_t res = 0;
  size_t threadsCount = 6;
  std::default_random_engine gen(seed);
  auto begin = std::chrono::high_resolution_clock::now();
  double square = getSquare(gen, numberOfTests, radius, threadsCount);
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast< std::chrono::milliseconds >(end - begin).count();
  std::cout << static_cast< double >(time) << "\n";
  auto begin1 = std::chrono::high_resolution_clock::now();
  double square1 = getSquareLin(gen, numberOfTests, radius);
  auto end1 = std::chrono::high_resolution_clock::now();
  auto time1 = std::chrono::duration_cast< std::chrono::milliseconds >(end1 - begin1).count();
  std::cout << static_cast< double >(time1) << "\n";
  return 0;
}
