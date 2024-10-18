#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include "calculate_square.hpp"
#include "scope_guard.hpp"

int main(int argc, char* argv[])
{
  int seed = 0;
  int tries = 0;
  if (argc == 2)
  {
    tries = std::stoi(argv[1]);
  }
  else if (argc == 3)
  {
    tries = std::stoi(argv[1]);
    seed = std::stoi(argv[2]);
  }
  else
  {
    std::cerr << "Error: Wrong command line arguments" << '\n';
    return 1;
  }

  if (seed < 0 || tries <= 0)
  {
    std::cerr << "Error: Wrong seed or tries" << '\n';
    return 1;
  }

  using namespace nikitov;
  int radius = 0;
  int numberOfThreads = 0;

  ScopeGuard scopeGuard(std::cout);
  std::cout << std::setprecision(3) << std::fixed;
  while (std::cin >> radius && std::cin >> numberOfThreads)
  {
    if (radius <= 0 || numberOfThreads <= 0)
    {
      std::cerr << "Error: Wrong radius or number of threads" << '\n';
      return 2;
    }
    auto begin = std::chrono::high_resolution_clock::now();
    double square = calculateSquare(radius, numberOfThreads, seed, tries);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast< std::chrono::milliseconds >(end - begin).count() << ' ' << square << '\n';
  }

  return 0;
}