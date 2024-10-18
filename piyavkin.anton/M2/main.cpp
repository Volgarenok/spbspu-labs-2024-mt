#include <iostream>
#include "circle.hpp"

int main()
{
  Circle c("abc", {3, 4}, 5);
  std::cout << c.name_ << ' ' << c.center_.x << ' ' << c.center_.y << ' ' << c.radius_;
}
