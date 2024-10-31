#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
#include <utility>

namespace kravchenko
{
  struct Point
  {
    int x;
    int y;
  };
  std::ostream& operator<<(std::ostream& out, const Point& p);

  struct Frame
  {
    Point p1;
    Point p2;
  };
  std::ostream& operator<<(std::ostream& out, const Frame& f);

  class Circle
  {
  public:
    Circle();
    Circle(int radius, int x, int y);
    int getRadius() const;
    const Point& getCenter() const;
    Frame getFrame() const;

  private:
    int radius_;
    Point center_;
  };
  std::istream& operator>>(std::istream& in, Circle& c);
  std::ostream& operator<<(std::ostream& out, const Circle& c);
}

#endif