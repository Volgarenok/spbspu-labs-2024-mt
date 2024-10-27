#ifndef POINT_HPP
#define POINT_HPP

namespace namestnikov
{
  struct Point
  {
  public:
    Point(double x, double y);
    double getX() const;
    double getY() const;
  private:
    double x_;
    double y_;
  };
}

#endif