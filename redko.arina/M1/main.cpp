#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

using point_t = std::pair< double, double >;
bool isPointInCircle(point_t p, double radius);

int main(int argc, char ** argv)
{
  int tries = 0;
  size_t seed = 0;
  try
  {
    if (argc == 2)
    {
      tries = std::stoi(argv[1]);
    }
    else if (argc == 3)
    {
      tries = std::stoi(argv[1]);
      seed = std::stoi(argv[2]);
    }
    else
    {
      std::cerr << "wrong number of parameters\n";
      return 1;
    }
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << "invalid command parameters\n";
    return 1;
  }

  if (tries <= 0 || seed < 0)
  {
    std::cerr << "non-positive number of tries or negative seed\n";
    return 2;
  }

  int numOfTreads = 0;
  int radius = 0;
  std::cin >> radius >> numOfTreads;
  if (radius <= 0 || numOfTreads <= 0)
  {
    std::cerr << "wrong input parameters\n";
    return 2;
  }

  std::vector< point_t > points(tries, {0,0});

  using namespace std::placeholders;
  size_t pointsInCircle = std::count_if(points.begin(), points.end(), std::bind(isPointInCircle, _1, radius));
  double frameArea = pow(2 * radius, 2);
  double circleArea = frameArea * (static_cast< double >(pointsInCircle) / static_cast< double >(tries));
  std::cout << circleArea << '\n';

  return 0;
}

bool isPointInCircle(point_t p, double radius)
{
  return pow(p.first, 2) + pow(p.second, 2) <= pow(radius, 2);
}
