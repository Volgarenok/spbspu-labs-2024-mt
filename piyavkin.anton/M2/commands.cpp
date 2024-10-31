#include "commands.hpp"
#include <cstddef>
#include <stdexcept>
#include <string.h>

void piyavkin::inputOb(std::istream& in, const std::string& name, circle_t& mp)
{
  Circle res;
  in >> res;
  if (!in)
  {
    throw std::logic_error("The circle is not created");
  }
  mp[name] = res;
}

void piyavkin::inputOb(std::istream& in, const std::string& nameSet, set_t& sets, const circle_t& c)
{
  long long n = 0;
  in >> n;
  if (!in)
  {
    throw std::logic_error("The set is not created");
  }
  if (n <= 0)
  {
    throw std::logic_error("The set is not created");
  }
  const size_t size = n;
  Set res;
  for (size_t i = 0; i < size; ++i)
  {
    std::string name;
    in >> name;
    if (c.find(name) != c.end())
    {
      res.insert(name, c.at(name));
    }
    else
    {
      throw std::logic_error("The set is not created");
    }
  }
  sets[nameSet] = res;
}
