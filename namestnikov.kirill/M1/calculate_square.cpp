#include "calculate_square.hpp"
#include <cmath>
#include <thread>
#include <future>
#include <algorithm>
#include <chrono>
#include <functional>
#include "point.hpp"

using data_t = std::vector< namestnikov::Point >;
using iterator_t = data_t::iterator;

bool checkIfInCircle(const namestnikov::Point & point, int radius)
{
  return (std::pow(point.getX(), 2) + std::pow(point.getY(), 2) <= std::pow(radius, 2)); 
}

void generatePoints(std::default_random_engine & gen, size_t count, int radius, data_t & data)
{
  std::uniform_real_distribution< double > distribution(-radius, radius);
  for (size_t i = 0; i < count; ++i)
  {
    double x = distribution(gen);
    double y = distribution(gen);
    namestnikov::Point p(x, y);
    data.push_back(p);
  }
}

size_t countPoints(const data_t & data, iterator_t begin, iterator_t end, int radius)
{
  using namespace std::placeholders;
  return std::count_if(begin, end, std::bind(checkIfInCircle, _1, radius));
}

double namestnikov::getSquare(std::default_random_engine & gen, size_t numberOfTests, int radius, size_t threadsCount)
{
  data_t data;
  data.reserve(numberOfTests);
  generatePoints(gen, numberOfTests, radius, data);
  size_t possibleThreads = std::thread::hardware_concurrency();
  threadsCount = std::min(possibleThreads, threadsCount);
  std::vector< std::future< size_t > > fts;
  fts.reserve(threadsCount - 1);
  std::vector< size_t > results(threadsCount, 0);
  size_t perThread = numberOfTests / threadsCount;
  size_t lastThread = perThread + numberOfTests % threadsCount;
  auto begin = data.begin();
  for (size_t i = 0; i < threadsCount - 1; ++i)
  {
    auto end = begin + perThread;
    fts.emplace_back(std::async(countPoints, std::cref(data), begin, end, radius));
    begin = end;
  }
  results.back() = countPoints(data, begin, begin + lastThread, radius);
  std::transform(fts.begin(), fts.end(), results.begin(),
   [](auto && ft)
   {
    return ft.get();
   });
   size_t res = std::accumulate(results.begin(), results.end(), 0);
   return 4 * std::pow(radius, 2) * res / numberOfTests; 
}