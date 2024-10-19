#include <algorithm>
#include <chrono>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
#include <utility>
#include "StreamGuard.hpp"

using Point = std::pair< double, double >;
using vec_p = std::vector< Point >;
using const_it_p = vec_p::const_iterator;
using val_it = std::vector< size_t >::iterator;

Point createPoint(double seed, std::random_device& randomDevice)
{
  std::uniform_real_distribution< double > randomDouble(0, seed + 15.0);
  Point p;
  auto tmp = randomDouble(randomDevice);
  p.first = tmp;
  tmp = randomDouble(randomDevice);
  p.second = tmp;
  return p;
}

vec_p generateValues(size_t tries, double seed, std::random_device& randomDevice)
{
  vec_p res(tries);
  auto func = std::bind(createPoint, seed, std::ref(randomDevice));
  std::generate(res.begin(), res.end(), func);
  return res;
}

bool isPointInsideCircle(const Point& p, size_t r)
{
  return (p.first * p.first) + (p.second * p.second) <= (r * r);
}

void checkInsidePoints(const_it_p begin, const_it_p end, double r, val_it res)
{
  *res = std::count_if(begin, end, std::bind(isPointInsideCircle, std::placeholders::_1, r));
}

double processMK(size_t r, size_t threads, size_t tries, double seed, std::random_device& randomDevice)
{
  if (threads > std::thread::hardware_concurrency() - 1)
  {
    threads = static_cast< size_t >(std::thread::hardware_concurrency() - 1);
  }
  std::vector< std::thread > ths;
  ths.reserve(threads - 1);
  size_t per_th = tries / threads;
  size_t last_th = per_th * tries % threads;
  vec_p points = generateValues(tries, seed, randomDevice);
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
  auto ratio = static_cast< double >(std::accumulate(res.cbegin(), res.cend(), 0ull) / tries);
  return ratio * 4 * r * r;
}

int main(int argc, char* argv[])
{
  if (argc > 3 || argc == 1)
  {
    std::cerr << "Input error - number of parameters\n";
    return 1;
  }
  size_t tries{};
  double seed{};
  try
  {

    if (argc == 3)
    {
      if (std::stoi(argv[1]) < 0 || std::stod(argv[2]) < 0)
      {
        throw std::invalid_argument("Parameters can't be negative\n");
      }
      tries = std::stoull(argv[1]);
      seed = std::stod(argv[2]);
    }
    else
    {
      tries = std::stoull(argv[1]);
    }
    size_t radius, countThreads{};
    std::random_device randomDevice;
    novokhatskiy::StreamGuard guard(std::cout);
    std::cout << std::setprecision(3) << std::fixed;
    while (!std::cin.eof())
    {
      std::cin >> radius >> countThreads;
      if (radius <= 0 || countThreads <= 0)
      {
        std::cerr << "Radius and amount of threads can't be negative or zero\n";
        continue;
      }
      auto init = std::chrono::high_resolution_clock::now();
      auto square = processMK(radius, countThreads, tries, seed, randomDevice);
      auto end = std::chrono::high_resolution_clock::now();
      auto time = std::chrono::duration_cast< std::chrono::milliseconds >(end - init).count();
      std::cout << time << ' ' << square << '\n';
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
