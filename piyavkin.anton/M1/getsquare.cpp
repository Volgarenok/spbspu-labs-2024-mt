#include "getsquare.hpp"
#include <thread>
#include <algorithm>
#include <vector>
#include <numeric>
#include <functional>

bool pred(const std::pair< double, double >& legs, double r)
{
  return legs.first * legs.first + legs.second * legs.second <= r * r;
}

void piyavkin::countPoints(const std::vector< std::pair< double, double > >& points, double r, size_t i, size_t amount, size_t& res)
{
  res = std::count_if(points.cbegin() + i, points.cbegin() + i + amount, std::bind(pred, std::placeholders::_1, r));
}

double piyavkin::getSquare(const std::vector< std::pair< double, double > >& points, size_t r, size_t countThreads)
{
  std::vector< std::thread > ths;
  ths.reserve(countThreads - 1);
  const size_t tries = points.size();
  size_t perTh = tries / countThreads;
  size_t lastTh = perTh + tries % countThreads;
  size_t i = 0;
  std::vector< size_t > results(countThreads, 0);
  for (; i < countThreads - 1; ++i)
  {
    ths.emplace_back(countPoints, std::cref(points), r, i * perTh, perTh, std::ref(results[i]));
  }
  countPoints(points, r, i * perTh, lastTh, results.back());
  for (auto && th: ths)
  {
    th.join();
  }
  return static_cast< double >(std::accumulate(results.cbegin(), results.cend(), 0)) / tries * (2 * r * 2 * r);
}