#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include "calculate_square.hpp"
#include "scope_guard.hpp"

int main(int argc, char* argv[])
{
  int inputTries = 0;
  int inputSeed = 0;
  try
  {
    if (argc == 2)
    {
      inputTries = std::stoi(argv[1]);
    }
    else if (argc == 3)
    {
      inputTries = std::stoi(argv[1]);
      inputSeed = std::stoi(argv[2]);
    }
    else
    {
      throw std::logic_error("Wrong number of agruments");
    }

    if (inputTries <= 0 || inputSeed < 0)
    {
      throw std::logic_error("Wrong seed or tries");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  size_t seed = inputSeed;
  size_t tries = inputTries;

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
      std::cout << std::chrono::duration_cast< std::chrono::milliseconds >(end - begin).count() << ' ' << square << '\n';
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 2;
  }

  return 0;
}