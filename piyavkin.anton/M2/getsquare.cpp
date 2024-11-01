#include "getsquare.hpp"
#include "base-types.hpp"
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <thread>

void piyavkin::countPoints(const data_t& points, const Set& set, size_t i, size_t amount, size_t& res)
{
  for (size_t j = i; j < i + amount; ++j)
  {
    if (set.isInside(points[j]))
    {
      ++res;
    }
  }
}

double piyavkin::getSquare(const data_t& points, const Set& set, const rectangle_t& r, size_t countThreads)
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
    ths.emplace_back(countPoints, std::cref(points), std::cref(set), i * perTh, perTh, std::ref(results[i]));
  }
  countPoints(points, set, i * perTh, lastTh, results.back());
  for (auto && th: ths)
  {
    th.join();
  }
  return static_cast< double >(std::accumulate(results.cbegin(), results.cend(), 0)) / tries * (r.ur.x - r.ll.x) * (r.ur.y - r.ll.y);
}