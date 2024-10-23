#include <cmath>
#include <random>
#include <vector>
#include <iostream>

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

bool checkIfInCircle(const Point & point, double radius)
{
  return (std::pow(point.getX(), 2) + std::pow(point.getY(), 2) <= std::pow(radius, 2)); 
}

int main()
{
  size_t seed = 5;
  double radius = 5.0;
  size_t numberOfTests = 5;
  size_t res = 0;
  std::default_random_engine gen(seed);
  std::uniform_real_distribution< double > distribution(-radius, radius);
  for (size_t i = 0; i < numberOfTests; ++i)
  {
    double x = distribution(gen);
    double y = distribution(gen);
    std::cout << x << " " << y;
    Point p(x, y);
    if (checkIfInCircle(p, radius))
    {
      ++res;
    }
  }
  std::cout << res;
  return 0;
}
