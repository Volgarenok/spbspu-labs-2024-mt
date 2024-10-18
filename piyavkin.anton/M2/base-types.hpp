#ifndef POINT_HPP
#define POINT_HPP

namespace piyavkin
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    point_t ll;
    point_t ur;
  };
}
#endif