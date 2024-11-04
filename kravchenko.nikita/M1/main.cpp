#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <stream_guard.hpp>
#include "compute_circle_area.hpp"

size_t getNonNegativeNumber(const char* arg)
{
  if (arg[0] == '-')
  {
    throw std::logic_error("Invalid input");
  }
  return std::stoull(arg);
}

int main(int argc, char* argv[])
{
  if (argc < 2 || 3 < argc)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }

  size_t tries = 0;
  size_t seed = 0;
  try
  {
    tries = getNonNegativeNumber(argv[1]);
    if (tries == 0)
    {
      throw std::logic_error("Invalid input");
    }
    if (argc == 3)
    {
      seed = getNonNegativeNumber(argv[2]);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  std::minstd_rand generator(seed);
  kravchenko::StreamGuard guard(std::cout);
  std::cout << std::setprecision(3) << std::fixed;
  long radius = 0;
  long threads = 0;
  while (std::cin >> radius >> threads)
  {
    if (radius <= 0 || threads <= 0)
    {
      std::cerr << "Invalid input";
      return 1;
    }
    try
    {
      using namespace kravchenko;
      using namespace std::chrono;
      const auto startTime = high_resolution_clock::now();
      DataPoint points = generateSamplePoints(tries, generator, radius);
      double area = computeCircleArea(points, radius, threads);
      const auto endTime = high_resolution_clock::now();
      std::cout << duration_cast< microseconds >(endTime - startTime).count() / 1000.0 << ' ';
      std::cout << area << '\n';
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
  return 0;
}
