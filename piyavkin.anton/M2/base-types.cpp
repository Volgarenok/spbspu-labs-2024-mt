#include "base-types.hpp"

std::ostream& piyavkin::operator<<(std::ostream& out, const point_t &p)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << p.x << ' ' << p.y << ')';
  return out;
}

std::ostream& piyavkin::operator<<(std::ostream& out, const rectangle_t& r)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << r.ll << ' ' << r.ur;
  return out;
}
