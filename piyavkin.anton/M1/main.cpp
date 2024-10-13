#include <iostream>
#include <stdexcept>
#include <string>
#include "createpoints.hpp"

int main(int argc, char* argv[])
{
  if (argc > 3 || argc < 2)
  {
    std::cerr << "The number of command line arguments does not meet the requirements\n";
    return 1;
  }
  try
  {
    if (argv[1][0] == '-')
    {
      throw std::logic_error("The number of tests is not positive");
    }
    size_t tries = std::stoull(argv[1]);
    size_t seed = 0;
    if (tries == 0)
    {
      throw std::logic_error("The number of tests is not positive");
    }
    if (argc == 3)
    {
      if (argv[2][0] == '-')
      {
        throw std::logic_error("The initialization value of the generator is negative");
      }
      seed = std::stoull(argv[2]);
    }
    long long r = 0;
    int countThread = 0;
    std::minstd_rand gen(seed);
    while (std::cin >> r >> countThread)
    {
      if (r <= 0 || countThread <= 0)
      {
        throw std::logic_error("The entered radius or number of threads is not positive");
      }
      std::vector< std::pair< double, double > > points;
      points.reserve(tries);
      piyavkin::createPoints(gen, points, r, tries);
      for (auto x: points)
      {
        std::cout << x.first << ' ' << x.second << '\n';
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
}