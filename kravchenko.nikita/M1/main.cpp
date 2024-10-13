#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <stream_guard.hpp>
#include "compute_circle_area.hpp"

size_t getNonNegative(const char* arg)
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
    tries = getNonNegative(argv[1]);
    if (tries == 0)
    {
      throw std::logic_error("Invalid input");
    }
    if (argc == 3)
    {
      seed = getNonNegative(argv[2]);
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
  while (!std::cin.eof())
  {
    size_t radius = 0;
    size_t threads = 0;
    try
    {
      if (!(std::cin >> radius && std::cin >> threads))
      {
        throw std::runtime_error("Failed input");
      }
      if (radius == 0 || threads == 0)
      {
        throw std::logic_error("Invalid input");
      }
      using namespace std::chrono;
      const time_point< system_clock > startTime = system_clock::now();
      double result = kravchenko::computeCircleArea(tries, generator, static_cast< double >(radius), threads);
      const time_point< system_clock > endTime = system_clock::now();
      std::cout << duration< double >(duration_cast< milliseconds >(endTime - startTime)).count() << ' ';
      std::cout << result << '\n';
    }
    catch (const std::logic_error& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}