#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <istream>
#include <map>
#include <string>
#include "circle.hpp"

namespace piyavkin
{
  void inputCircle(std::istream& in, std::map< std::string, Circle >& mp);
}
#endif