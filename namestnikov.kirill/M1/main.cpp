#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include "calculate_square.hpp"
#include "stream_guard.hpp"

int main(int argc, char * argv[])
{
  using namespace namestnikov;
  int numberOfTests = 0;
  int seed = 0;
  try
  {
    if (argc == 3)
    {
      numberOfTests = std::stoi(argv[1]);
      seed = std::stoi(argv[2]);
    }
    else if (argc == 2)
    {
      numberOfTests = std::stoi(argv[1]);
    }
    else
    {
      std::cerr << "Wrong command line arguments\n";
      return 1;
    }
    if ((numberOfTests < 0) || (seed < 0))
    {
      std::cerr << "Command line arguments must not be less than zero\n";
      return 1;
    }
    std::default_random_engine gen(seed);
    StreamGuard guard(std::cout);
    std::cout << std::setprecision(3) << std::fixed;
    int radius = 0;
    int threadsCount = 0;
    while (std::cin >> radius >> threadsCount)
    {
      if ((radius < 0) || (threadsCount < 0))
      {
        std::cerr << "Arguments must not be less than zero\n";
        return 1;
      }
      auto begin = std::chrono::high_resolution_clock::now();
      double square = getSquare(gen, numberOfTests, radius, threadsCount);
      auto end = std::chrono::high_resolution_clock::now();
      auto time = std::chrono::duration_cast< std::chrono::milliseconds >(end - begin).count();
      std::cout << static_cast< double >(time) << " " << square << "\n";
    }
    if (!std::cin.eof())
    {
      std::cerr << "Wrong input\n";
      return 1;
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
