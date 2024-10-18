#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include "streamGuard.hpp"
#include "function.hpp"

/*size_t getNumber(char* s)
{
  if (s[0] == '-')
  {
    throw std::logic_error("It is not positive number\n");
  }
  return std::stoull(s);
}*/

int main(int argc, char* argv[])
{
  if (argc > 3 || argc < 2)
  {
    std::cerr << "The number of command line arguments does not meet the requirements\n";
    return 1;
  }
  int tries = 0;
  int seed = 0;
  try
  {
    tries = std::stoi(argv[1]);
    if (argc == 3)
    {
      seed = std::stoi(argv[2]);
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  if (tries <= 0 || seed < 0)
  {
    std::cerr << "the number of tests is not positive or generator initialization value is negative\n";
    return 3;
  }
  using namespace erfurt;
  std::chrono::steady_clock timer;
  double radius = 0;
  int threads = 0;
  while (std::cin >> radius >> threads)
  {
    if (radius <= 0 || threads <= 0)
    {
      std::cerr << "The entered radius or threads is not positive";
      return 4;
    }
    double square = 0.0;
    auto start = timer.now();
    try
    {
        square = getSquare(static_cast<size_t>(seed), static_cast<size_t>(tries), radius, static_cast<size_t>(threads));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 5;
    }
    auto end = timer.now();
    StreamGuard guard(std::cout);
    std::cout << std::fixed << std::setprecision(3);
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ";
    std::cout << square << '\n';
  }
  if (!std::cin.eof())
  {
    std::cerr << "Incorrect radius or number of threads\n";
    return 6;
  }
  return 0;
}