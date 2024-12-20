#include "set.hpp"
#include <cstddef>

void piyavkin::Set::insert(const Circle& c)
{
  set_.push_back(c);
  rectangle_.ll.x = std::min(c.getFrame().ll.x, rectangle_.ll.x);
  rectangle_.ll.y = std::min(c.getFrame().ll.y, rectangle_.ll.y);
  rectangle_.ur.x = std::max(c.getFrame().ur.x, rectangle_.ur.x);
  rectangle_.ur.y = std::max(c.getFrame().ur.y, rectangle_.ur.y);
}

const piyavkin::rectangle_t& piyavkin::Set::getFrame() const
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
  
  auto it = s.set_.cbegin();
  for (; it != --s.set_.cend(); ++it)
  {
    out << *it << '\n';
  }
  out << *it;
  return out;
}

std::string piyavkin::Set::getStr() const
{
  std::string res;
  res += std::to_string(set_.size()) + ' ';
  size_t i = 0;
  for (; i < set_.size() - 1; ++i)
  {
    res += set_[i].getStr() + ' ';
  }
  res += set_[i].getStr();
  return res;
}

piyavkin::Set piyavkin::parse(const std::string& str)
{
  size_t sp = str.find(' ');
  std::string ns = str.substr(0, sp);
  size_t n = std::stoull(ns);
  Set st;
  size_t curr = sp + 1;
  std::vector< double > c(3, 0);
  for (size_t i = 0 ; i < n; ++i)
  {
    for (size_t j = 0; j < 3; ++j)
    {
      sp = str.find(' ', curr);
      ns = str.substr(curr, sp);
      c[j] = std::stod(ns);
      curr = sp + 1;
    }
    Circle circle({c[1], c[2]}, c[0]);
    st.insert(circle);
  }
  return st;
}

bool piyavkin::Set::isInside(const std::pair< double, double >& p) const
{
  for (size_t i = 0; i < set_.size(); ++i)
  {
    if (set_[i].isInside(p))
    {
      return true;
    }
  }
  return false;
}