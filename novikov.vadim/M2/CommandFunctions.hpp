#ifndef COMMAND_FUNCTIONS_HPP
#define COMMAND_FUNCTIONS_HPP

#include <iosfwd>
#include <string>
#include <vector>
#include <unordered_map>
#include <Circle.hpp>

namespace novikov
{
  using circle_collection_t = std::unordered_map< std::string, Circle >;
  using circle_set_collection_t = std::unordered_map< std::string, std::vector< std::string > >;

  namespace cmd
  {
    void circle(std::istream& in, std::ostream& out, circle_collection_t& circles);
    void set(std::istream& in, std::ostream& out, circle_set_collection_t& circle_sets);
    void show(std::istream& in, std::ostream& out, const circle_collection_t& circles);
    void showset(std::istream& in, std::ostream& out, const circle_collection_t& circles, const circle_set_collection_t& circle_sets);
  }	  
}

#endif
