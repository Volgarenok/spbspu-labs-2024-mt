#include "commands.hpp"

void piyavkin::inputOb(std::istream& in, const std::string& name, circle_t& mp)
{
  Circle res;
  in >> res;
  if (!in)
  {
    throw std::logic_error("The object is not created");
  }
  mp[name] = res;
}

void piyavkin::inputOb(std::istream& in, const std::string& nameSet, set_t& sets, const circle_t& c)
{
  size_t n = 0;
  in >> n;
  if (!in)
  {
    throw std::logic_error("The object is not created");
  }
  Set res;
  for (size_t i = 0; i < n; ++i)
  {
    std::string name;
    in >> name;
    if (c.find(name) != c.end())
    {
      res.insert(name, c.at(name));
    }
    else
    {
      throw std::logic_error("The object is not created");
    }
  }
  sets[nameSet] = res;
}
