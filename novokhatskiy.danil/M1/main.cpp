#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <exception>
#include <thread>
#include "StreamGuard.hpp"

using Point = std::pair< double, double >;
using vec_p = std::vector< Point >;

Point createPoint(double seed, std::random_device& randomDevice)
{
  std::uniform_real_distribution< double > randomDouble(seed, seed + 15.0);
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

bool isPointInsideCircle(size_t r, Point& p)
{
  return (p.first * p.first) + (p.second * p.second) <= (r * r);
}

double processMK(size_t r, size_t threads, size_t tries, double seed, std::random_device& randomDevice)
{
  size_t insidePoints{0};
  if (threads > std::thread::hardware_concurrency() - 1)
  {
    threads = static_cast< size_t >(std::thread::hardware_concurrency() - 1);
  }
  std::vector< std::thread > ths;
  ths.reserve(threads - 1);
  size_t per_th = tries / threads;
  for (size_t i = 0; i < tries; ++i)
  {
    Point p = createPoint(seed, randomDevice);
    if (isPointInsideCircle(r, p))
    {
      insidePoints++;
    }
  }
  for (auto && th : ths)
  {
    th.join();
  }
  auto ratio = static_cast< double >(insidePoints / tries);
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
      processMK(radius, countThreads, tries, seed, randomDevice);
      std::cout << '\n';
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
