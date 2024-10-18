#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <istream>
#include <map>
#include <ostream>
#include <string>
#include <stdexcept>

namespace piyavkin
{
  template< class T >
  void input(std::istream& in, std::map< std::string, T >& mp)
  {
    std::string name;
    in >> name;
    if (mp.find(name) != mp.end())
    {
      throw std::logic_error("The object is not created");
    }
    T t;
    in >> t;
    if (!in)
    {
      throw std::logic_error("The object is not created");
    }
    mp[name] = t;
  }
  template< class T >
  void output(std::istream& in, std::ostream& out, const std::map< std::string, T >& mp)
  {
    std::string name;
    in >> name;
    out << mp.at(name) << '\n';
  }
  template< class T >
  void outputFrame(std::istream& in, std::ostream& out, const std::map< std::string, T >& mp)
  {
    std::string name;
    in >> name;
    out << mp.at(name).getFrame() << '\n';
  }
}
#endif