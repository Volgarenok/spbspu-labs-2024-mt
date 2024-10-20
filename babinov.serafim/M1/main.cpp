#include <algorithm>
#include <chrono>
#include <future>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

#include "circles.hpp"

double calculateArea(babinov::CircleData data, size_t seed, size_t tries)
{
  std::vector< std::future< size_t > > futures;
  futures.reserve(data.nThreads - 1);
  std::vector< size_t > results(data.nThreads, 0);

  size_t ts = tries;
  size_t triesForOne = tries / data.nThreads;
  for (size_t i = 0; i < data.nThreads - 1; ++i, ts -= triesForOne)
  {
    futures.emplace_back(std::async(babinov::calculateTargetPoints, seed, triesForOne, tries - ts, data.radius));
  }
  results.back() = babinov::calculateTargetPoints(seed, ts, tries - ts, data.radius);
  std::transform(futures.begin(), futures.end(), results.begin(),
   [](auto && ft)
   {
     return ft.get();
   });
  return std::accumulate(results.cbegin(), results.cend(), 0.0) / tries * 4 * data.radius * data.radius;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Too few arguments" << '\n';
    return 1;
  }
  int tries = 0;
  int seed = 0;
  try
  {
    tries = std::stoi(argv[1]);
    if (argc > 2)
    {
      seed = std::stoi(argv[2]);
    }
    if ((tries <= 0) || (seed < 0))
    {
      throw std::invalid_argument("");
    }
  }
  catch (const std::invalid_argument&)
  {
    std::cerr << "Invalid arguments" << '\n';
    return 1;
  }

  babinov::CircleData data;
  std::cout << std::setprecision(3) << std::fixed;
  while (std::cin >> data)
  {
    auto start = std::chrono::steady_clock::now();
    double area = calculateArea(data, seed, tries);
    auto end = std::chrono::steady_clock::now();
    double time = std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count();
    std::cout << time << ' ' << area << '\n';
  }
  if (!std::cin.eof())
  {
    std::cerr << "Invalid values" << '\n';
    return 1;
  }
  return 0;
}
