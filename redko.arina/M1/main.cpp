#include <iostream>
#include <iomanip>
#include <chrono>
#include "areaProcessing.hpp"

int main(int argc, char ** argv)
{
  int tries = 0;
  int seed = 0;
  try
  {
    if (argc == 2)
    {
      tries = std::stoll(argv[1]);
    }
    else if (argc == 3)
    {
      tries = std::stoll(argv[1]);
      seed = std::stoll(argv[2]);
    }
    else
    {
      std::cerr << "wrong number of parameters\n";
      return 1;
    }
  }
  catch (const std::exception &)
  {
    std::cerr << "invalid command parameters\n";
    return 1;
  }

  if (tries <= 0 || seed < 0)
  {
    std::cerr << "non-positive number of tries or negative seed\n";
    return 2;
  }

  std::cout << std::fixed << std::setprecision(3);
  int numOfThreads = 0;
  int radius = 0;
  while (std::cin >> radius >> numOfThreads)
  {
    if (radius <= 0 || numOfThreads <= 0)
    {
      std::cerr << "wrong input parameters\n";
      return 2;
    }
    auto begin = std::chrono::steady_clock::now();
    double area = redko::calculateCircleArea(radius, numOfThreads, tries, seed);
    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast< std::chrono::milliseconds >(end - begin);
    std::cout << time.count() << ' ' << area << '\n';
  }
  if (!std::cin.eof())
  {
    std::cerr << "invalid input\n";
    return 1;
  }
  return 0;
}
