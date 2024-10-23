#include <cmath>
#include <random>
#include <thread>
#include <vector>
#include <iostream>
#include <future>
#include <algorithm>
#include <chrono>

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

bool checkIfInCircle(const Point & point, int radius)
{
  return (std::pow(point.getX(), 2) + std::pow(point.getY(), 2) <= std::pow(radius, 2)); 
}

size_t countPoints(std::default_random_engine & gen, size_t numberOfTests, int radius)
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
  return res;
}

double getSquare(std::default_random_engine & gen, size_t numberOfTests, int radius, size_t threadsCount)
{
  size_t possibleThreads = std::thread::hardware_concurrency();
  threadsCount = std::min(possibleThreads, threadsCount);
  std::vector< std::future< size_t > > fts;
  fts.reserve(threadsCount - 1);
  std::vector< size_t > results(threadsCount, 0);
  for (size_t i = 0; i < threadsCount - 1; ++i)
  {
    fts.emplace_back(std::async(countPoints, std::ref(gen), numberOfTests / threadsCount, radius));
  }
  results.back() = countPoints(gen, numberOfTests / threadsCount + numberOfTests % threadsCount, radius);
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
  std::cout << static_cast< double >(time);
  //res = countPoints(gen, numberOfTests, radius);
  std::cout << 4 * std::pow(radius, 2) * res / numberOfTests << "\n";
  std::cout << 3.1415 * radius * radius;
  return 0;
}
