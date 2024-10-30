#include "StringParseFunctions.hpp"
#include <cctype>

bool novikov::containsOnlyNumbers(const std::string& str)
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
