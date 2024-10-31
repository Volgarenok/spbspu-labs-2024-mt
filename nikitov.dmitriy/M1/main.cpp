#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include "calculate_square.hpp"
#include "scope_guard.hpp"

int main(int argc, char* argv[])
{
  size_t seed = 0;
  size_t tries = 0;
  try
  {
    if (argc != 2 && argc != 3)
    {
      throw std::logic_error("Wrong input parameters");
    }
    
    if (argv[1][0] == '-')
    {
      throw std::logic_error("The number of tries is negative");
    }
    tries = std::stoi(argv[1]);

    if (argc == 3)
    {
      if (argv[2][0] == '-')
      {
        throw std::logic_error("Seed is negative");
      }
      seed = std::stoi(argv[2]);
    }

    if (tries == 0)
    {
      throw std::logic_error("The number of tries is 0");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  using namespace nikitov;
  ScopeGuard scopeGuard(std::cout);
  std::cout << std::setprecision(3) << std::fixed;

  int radius = 0;
  int numberOfThreads = 0;
  try
  {
    while (std::cin >> radius && std::cin >> numberOfThreads)
    {
      if (radius <= 0 || numberOfThreads <= 0)
      {
        throw std::logic_error("Error: Wrong radius or number of threads");
      }
      auto begin = std::chrono::high_resolution_clock::now();
      double square = calculateSquare(radius, numberOfThreads, seed, tries);
      auto end = std::chrono::high_resolution_clock::now();
      auto time = std::chrono::duration_cast< std::chrono::microseconds >(end - begin).count();
      std::cout << static_cast< double >(time) / 1000 << ' ' << square << '\n';
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 2;
  }

  return 0;
}

