#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include "streamGuard.hpp"
#include "function.hpp"

size_t getNumber(char* s)
{
  if (s[0] == '-')
  {
    throw std::logic_error("Invalid command line arguments");
  }
  return std::stoull(s);
}

int main(int argc, char* argv[])
{
  if (argc > 3 || argc < 2)
  {
    std::cerr << "The number of command line arguments does not meet the requirements\n";
    return 1;
  }
  size_t tries = 0;
  size_t seed = 0;
  try
  {
    tries = getNumber(argv[1]);
    if (tries == 0)
    {
      throw std::logic_error("The number of tests is not positive");
    }
    if (argc == 3)
    {
      seed = getNumber(argv[2]);
    }
  }
  catch (const std::logic_error& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  using namespace erfurt;
  std::chrono::steady_clock timer;
  double radius = 0;
  int threads = 0;
  while (std::cin >> radius >> threads)
  {
    if (radius < 0 || threads < 0)
    {
      std::cerr << "The entered radius or number of threads is not positive";
    }
    auto start = timer.now();
    double square = getSquare(seed, tries, radius, threads);
    auto end = timer.now();
    StreamGuard guard(std::cout);
    std::cout << std::fixed << std::setprecision(3);
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ";
    std::cout << square << '\n';
  }
  if (!std::cin.eof())
  {
    std::cerr << "Incorrect radius or number of threads\n";
    return 3;
  }
  return 0;
}