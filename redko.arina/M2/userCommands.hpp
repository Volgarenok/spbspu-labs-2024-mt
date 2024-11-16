#ifndef USERCOMMANDS_HPP
#define USERCOMMANDS_HPP
#include <istream>
#include "calculation.hpp"

namespace redko
{
  void createCircle(std::istream & in, map_t &, set_t & circleSet, std::map< std::string, Calculation > &, std::ostream &);
  void createSet(std::istream & in, map_t & setMap, set_t & circleSet, std::map< std::string, Calculation > &, std::ostream &);
  void showCircle(std::istream & in, map_t &, set_t & circleSet, std::map< std::string, Calculation > &, std::ostream & out);
  void showSet(std::istream & in, map_t & setMap, set_t &, std::map< std::string, Calculation > &, std::ostream & out);
  void showCircleFrame(std::istream & in, map_t &, set_t & circleSet, std::map< std::string, Calculation > &, std::ostream & out);
  void showSetFrame(std::istream & in, map_t & setMap, set_t &, std::map< std::string, Calculation > &, std::ostream & out);
  void calculateSetArea(std::istream & in, map_t & setMap, set_t &, std::map< std::string, Calculation > & calcs, std::ostream &);
  void showStatus(std::istream & in, map_t &, set_t &, std::map< std::string, Calculation > & calcs, std::ostream & out);
  void wait(std::istream & in, map_t &, set_t &, std::map< std::string, Calculation > & calcs, std::ostream & out);
}

#endif
