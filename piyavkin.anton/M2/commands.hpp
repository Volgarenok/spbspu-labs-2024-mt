#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "set.hpp"
#include <map>

namespace piyavkin
{
  using circle_t = std::map< std::string, Circle >;
  using set_t = std::map< std::string, Set >;
  using calc_t = std::map< std::string, double >;
  void inputOb(std::istream& in, const std::string& name, circle_t& mp);
  void inputOb(std::istream& in, const std::string& name, set_t& sets, const circle_t& c);
  template< class T, class... Args >
  void input(std::istream& in, Args&&... args)
  {
    std::string name;
    in >> name;
    auto a = std::make_tuple(std::forward< Args >(args)...);
    auto mp = std::get< 0 >(a);
    if (mp.find(name) != mp.end())
    {
      throw std::logic_error("The object is not created");
    }
    inputOb(in, name, std::forward< Args >(args)...);
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
  void calcArea(std::istream& in, set_t& sets, calc_t& calcs, int socket);
}
#endif