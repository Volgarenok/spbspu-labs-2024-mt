#include <iostream>
#include "areaProcessing.hpp"

int main(int argc, char ** argv)
{
  int tries = 0;
  size_t seed = 0;
  try
  {
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
      std::cerr << "wrong number of parameters\n";
      return 1;
    }
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << "invalid command parameters\n";
    return 1;
  }

  if (tries <= 0 || seed < 0)
  {
    std::cerr << "non-positive number of tries or negative seed\n";
    return 2;
  }

  int numOfThreads = 0;
  int radius = 0;
  std::cin >> radius >> numOfThreads;
  if (radius <= 0 || numOfThreads <= 0)
  {
    std::cerr << "wrong input parameters\n";
    return 2;
  }

  double circleArea = redko::calculateCircleArea(radius, numOfThreads, tries, seed);
  std::cout << circleArea << '\n';

  return 0;
}
