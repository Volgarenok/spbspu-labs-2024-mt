#include "getpositivenum.hpp"
#include <stdexcept>
#include <string>

size_t piyavkin::getPositiveNum(char* str)
{
  if (str[0] == '-')
  {
    throw std::logic_error("Negative number in command line");
  }
  return std::stoull(str);
}
