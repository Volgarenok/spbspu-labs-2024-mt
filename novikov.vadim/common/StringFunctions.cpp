#include "StringFunctions.hpp"
#include <cctype>
#include <stdexcept>

bool novikov::isSizeType(const std::string& str)
{
  for (auto&& i : str)
  {
    if (!std::isdigit(i))
    {
      return false;
    }
  }

  return true;
}

size_t novikov::parseSizeType(const std::string& str)
{
  if (!isSizeType(str))
  {
    throw std::invalid_argument("Некорректные параметры!");
  }

  return std::stoul(str);
}
