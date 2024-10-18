#include "commands.hpp"
#include <stdexcept>
#include <string>

void piyavkin::inputCircle(std::istream& in, std::map< std::string, Circle >& mp)
{
  std::string name;
  in >> name;
  Circle c({0, 0}, 0);
  in >> c;
  if (!in)
  {
    throw std::logic_error("The circle is not created");
  }
  mp[name] = c;
}