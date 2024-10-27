#include <cmath>
#include <random>
#include <thread>
#include <vector>
#include <iostream>
#include <future>
#include <algorithm>
#include <chrono>
#include <functional>


struct Point{
public:
  Point(double x, double y):
    x_(x),
    y_(y)
  {}
  double getX() const
  {
    return x_;
  }
  double getY() const
  {
    return y_;
  }
private:
  double x_;
  double y_;
};

using data_t = std::vector< Point >;
using iterator_t = data_t::iterator;

bool checkIfInCircle(const Point & point, int radius)
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
    Point p(x, y);
    data.push_back(p);
  }
}

size_t countPoints(const data_t & data, iterator_t begin, iterator_t end, int radius)
{
  using namespace std::placeholders;
  return std::count_if(begin, end, std::bind(checkIfInCircle, _1, radius));
}

double getSquareLin(std::default_random_engine & gen, size_t numberOfTests, int radius)
{
  std::uniform_real_distribution< double > distribution(-radius, radius);
  int res = 0;
  for (size_t i = 0; i < numberOfTests; ++i)
  {
    double x = distribution(gen);
    double y = distribution(gen);
    //std::cout << x << " " << y;
    Point p(x, y);
    if (checkIfInCircle(p, radius))
    {
      ++res;
    }
  }
  return 4 * std::pow(radius, 2) * res / numberOfTests;
}

double getSquare(std::default_random_engine & gen, size_t numberOfTests, int radius, size_t threadsCount)
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

int main()
{
  size_t seed = 5;
  int radius = 2;
  size_t numberOfTests = 100000000;
  size_t res = 0;
  size_t threadsCount = 6;
  std::default_random_engine gen(seed);
  auto begin = std::chrono::high_resolution_clock::now();
  double square = getSquare(gen, numberOfTests, radius, threadsCount);
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast< std::chrono::milliseconds >(end - begin).count();
  std::cout << static_cast< double >(time) << "\n";
  auto begin1 = std::chrono::high_resolution_clock::now();
  double square1 = getSquareLin(gen, numberOfTests, radius);
  auto end1 = std::chrono::high_resolution_clock::now();
  auto time1 = std::chrono::duration_cast< std::chrono::milliseconds >(end1 - begin1).count();
  std::cout << static_cast< double >(time1) << "\n";
  return 0;
}
