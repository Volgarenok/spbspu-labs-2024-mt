#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <iomanip>
#include <streamguard.hpp>
#include <getpositivenum.hpp>
#include "createpoints.hpp"
#include "getsquare.hpp"

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
    tries = piyavkin::getPositiveNum(argv[1]);
    if (tries == 0)
    {
      throw std::logic_error("The number of tests equil 0");
    }
    if (argc == 3)
    {
      seed = piyavkin::getPositiveNum(argv[2]);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  double r = 0;
  long countThreads = 0;
  while (std::cin >> r >> countThreads)
  {
    if (r <= 0 || countThreads <= 0)
    {
      std::cerr << "The entered radius or number of threads is not positive\n";
      return 3;
    }
    try
    {
      using namespace piyavkin;
      data_t points;
      points.reserve(tries);
      std::minstd_rand gen(seed);
      createPoints(gen, points, r, tries);
      auto start = std::chrono::high_resolution_clock::now();
      double square = getSquare(points, r, countThreads);
      auto end = std::chrono::high_resolution_clock::now();
      auto mcs = std::chrono::duration_cast< std::chrono::microseconds >(end - start).count();
      StreamGuard guard(std::cout);
      std::cout << std::fixed << std::setprecision(3);
      std::cout << static_cast< double >(mcs) / 1000 << ' ' << square << '\n';
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 4;
    }
  }
  if (!std::cin.eof())
  {
    std::cerr << "Incorrect radius or number of threads\n";
    return 3;
  }
}
