#include "calculate_square.hpp"
#include <cstdlib>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>

double calculateSquare(int radius, int numberOfThreads, int seed)
{
  std::srand(seed);
  std::vector< std::future< double > > futures;
  futures.reserve(numberOfThreads);
  std::vector< double > squares(numberOfThreads, 0.0);
  for (int i = 0; i != numberOfThreads; ++i)
  {
    continue;
  }

  return 0.0;
}