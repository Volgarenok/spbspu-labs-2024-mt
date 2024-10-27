#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>

namespace kravchenko
{
  struct Point
  {
    int x;
    int y;
  };
  std::ostream& operator<<(std::ostream& out, const Point& p);

  class Circle
  {
  public:
    Circle();
    Circle(int radius, int x, int y);
    int getRadius() const;
    const Point& getCenter() const;

  private:
    int radius_;
    Point center_;
  };
  std::istream& operator>>(std::istream& in, Circle& c);
  std::ostream& operator<<(std::ostream& out, const Circle& c);
}

#endif