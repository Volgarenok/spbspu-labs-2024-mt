#include "circle.hpp"

std::ostream & redko::operator<<(std::ostream & out, const Circle & circle)
{
  out << circle.radius << ' ' << circle.center;
  return out;
}

bool redko::operator<(const std::string & name, const Circle & circle)
{
  return name < circle.name;
}
bool redko::operator<(const Circle & circle, const std::string & name)
{
  return circle.name < name;
}
bool redko::operator<(const Circle & firstCircle, const Circle & secondCircle)
{
  return firstCircle.name < secondCircle.name;
}
