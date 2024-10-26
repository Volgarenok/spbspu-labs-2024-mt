#include <chrono>
#include <iomanip>
#include <iostream>

#include "calculateSquare.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2 && argc != 3)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  size_t iterations = 0;
  size_t seed = 0;
  try
  {
    bool hasNegative = true;
    if (argv[1][0] != '-')
    {
      iterations = std::stoull(argv[1]);
      hasNegative = false;
    }
    if (argc == 3)
    {
      if (!hasNegative && argv[2][0] != '-')
      {
        seed = std::stoull(argv[2]);
      }
      else
      {
        hasNegative = true;
      }
    }
    if (hasNegative)
    {
      throw std::invalid_argument("main.cpp: negative app args");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  std::string radiusStr;
  std::string threadsStr;
  std::cout << std::setprecision(3) << std::fixed;
  try
  {
    while (std::cin >> radiusStr >> threadsStr)
    {
      size_t radius = 0;
      size_t threads = 0;
      if (radiusStr[0] != '-' && threadsStr[0] != '-')
      {
        radius = std::stoull(radiusStr);
        threads = std::stoull(threadsStr);
      }
      else
      {
        throw std::invalid_argument("main.cpp: negative cmd args");
      }
      auto start = std::chrono::high_resolution_clock::now();
      double square = zhalilov::calcCircleSquare(radius, threads, iterations, seed);
      auto end = std::chrono::high_resolution_clock::now();
      double time = std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count();
      std::cout << time << ' ' << square << '\n';
    }
    if (!std::cin)
    {
      throw std::invalid_argument("main.cpp: !std::cin");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
