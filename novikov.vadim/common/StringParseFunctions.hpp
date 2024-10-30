#ifndef STRING_PARSE_FUNCTIONS_HPP
#define STRING_PARSE_FUNCTIONS_HPP

#include <cstddef>
#include <string>

namespace novikov
{
  bool isSizeType(const std::string& str);
  size_t parseSizeType(const std::string& str);
}

#endif
