#include "set.hpp"

void piyavkin::Set::insert(const std::string& name, const Circle &c)
{
  set_.insert({name, c});
  rectangle_.ll.x = std::min(c.getFrame().ll.x, rectangle_.ll.x);
  rectangle_.ll.y = std::min(c.getFrame().ll.y, rectangle_.ll.y);
  rectangle_.ur.x = std::max(c.getFrame().ur.x, rectangle_.ur.x);
  rectangle_.ur.y = std::max(c.getFrame().ur.y, rectangle_.ur.y);
}

piyavkin::rectangle_t piyavkin::Set::getFrame() const
{
  return rectangle_;
}

std::ostream& piyavkin::operator<<(std::ostream& out, const Set& s)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  for (auto x: s.set_)
  {
    out << x.first << ' ' << x.second;
  }
  return out;
}