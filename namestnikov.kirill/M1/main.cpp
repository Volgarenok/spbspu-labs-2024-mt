#include <cmath>
#include <random>
#include <thread>
#include <vector>
#include <iostream>
#include <future>
#include <algorithm>

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

size_t countPoints(std::default_random_engine & gen, size_t numberOfTests, int radius, size_t skipsCount)
{
  std::uniform_real_distribution< double > distribution(-radius, radius);
  for (size_t i = 0; i < skipsCount; ++i)
  {
    distribution(gen);
  }
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
  size_t skipsCount = 0;
  for (size_t i = 0; i < threadsCount - 1; ++i)
  {
    fts.emplace_back(std::async(countPoints, std::ref(gen), numberOfTests / threadsCount, radius, skipsCount));
    skipsCount += numberOfTests / threadsCount;
  }
  results.back() = countPoints(gen, numberOfTests / threadsCount + numberOfTests % threadsCount, radius, skipsCount);
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
  double radius = 5;
  size_t numberOfTests = 10000000;
  size_t res = 0;
  std::default_random_engine gen(seed);
  //res = countPoints(gen, numberOfTests, radius);
  std::cout << 4 * std::pow(radius, 2) * res / numberOfTests << "\n";
  std::cout << 3.1415 * radius * radius;
  return 0;
}
