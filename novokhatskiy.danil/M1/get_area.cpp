#include "get_area.hpp"
#include <algorithm>
#include <functional>
#include <thread>

novokhatskiy::Point novokhatskiy::createPoint(size_t r, std::minstd_rand& randomDevice)
{
  std::uniform_real_distribution< double > randomDouble(0, r);
  novokhatskiy::Point p;
  auto tmp = randomDouble(randomDevice);
  p.first = tmp;
  tmp = randomDouble(randomDevice);
  p.second = tmp;
  return p;
}

novokhatskiy::vec_p novokhatskiy::generateValues(size_t tries, size_t r, std::minstd_rand& randomDevice)
{
  novokhatskiy::vec_p res(tries);
  auto func = std::bind(createPoint, r, std::ref(randomDevice));
  std::generate(res.begin(), res.end(), func);
  return res;
}

bool novokhatskiy::isPointInsideCircle(const novokhatskiy::Point & p, size_t r)
{
  return (p.first * p.first) + (p.second * p.second) <= (r * r);
}

void novokhatskiy::checkInsidePoints(novokhatskiy::const_it_p begin, novokhatskiy::const_it_p end, size_t r, novokhatskiy::val_it res)
{
  *res = std::count_if(begin, end, std::bind(isPointInsideCircle, std::placeholders::_1, r));
}

double novokhatskiy::processMK(size_t r, size_t threads, size_t tries, std::minstd_rand& randomDevice)
{
  if (threads > std::thread::hardware_concurrency() - 1)
  {
    threads = static_cast< size_t >(std::thread::hardware_concurrency() - 1);
  }
  std::vector< std::thread > ths;
  ths.reserve(threads - 1);
  size_t per_th = tries / threads;
  size_t last_th = per_th * tries % threads;
  novokhatskiy::vec_p points = generateValues(tries, r, randomDevice);
  auto begin = points.begin();
  std::vector< size_t > res(threads, 0);
  for (size_t i = 0; i < threads - 1; ++i)
  {
    auto end = begin + per_th;
    ths.emplace_back(checkInsidePoints, begin, end, r, res.begin() + i);
    begin = end;
  }
  checkInsidePoints(begin, begin + last_th, r, res.end() - 1);
  for (auto&& th : ths)
  {
    th.join();
  }
  double ratio = std::accumulate(res.cbegin(), res.cend(), 0ull) / static_cast< double >(tries);
  return ratio * 4 * r * r;
}
