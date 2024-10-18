#include "commands.hpp"
#include "circle.hpp"
#include <stdexcept>
#include <string>

void piyavkin::inputCircle(std::istream& in, std::map< std::string, Circle >& mp)
{
  std::string name;
  in >> name;
  if (mp.find(name) != mp.end())
  {
    throw std::logic_error("The circle is not created");
  }
  Circle c({0, 0}, 0);
  in >> c;
  if (!in)
  {
    throw std::logic_error("The circle is not created");
  }
  mp[name] = c;
}

void piyavkin::outputCircle(std::istream& in, std::ostream& out, const std::map< std::string, Circle >& mp)
{
  std::string name;
  in >> name;
  out << mp.at(name) << '\n';
}

void piyavkin::outputFrameCircle(std::istream& in, std::ostream& out, const std::map< std::string, Circle >& mp)
{
  std::string name;
  in >> name;
  out << mp.at(name).getFrame() << '\n';
}

void piyavkin::inputSet(std::istream& in, std::map< std::string, Set >& sets, const std::map< std::string, Circle >& circles)
{
  std::string name;
  in >> name;
  if (sets.find(name) != sets.end())
  {
    throw std::logic_error("The circle is not created");
  }
  Set st;
  size_t n = 0;
  in >> n;
  if (!in)
  {
    throw std::logic_error("The set is not created");
  }
  std::string nameCircle;
  for (size_t i = 0; i < n; ++i)
  {
    in >> nameCircle;
    st.insert(circles.at(nameCircle));
  }
  sets[name] = st;
}
