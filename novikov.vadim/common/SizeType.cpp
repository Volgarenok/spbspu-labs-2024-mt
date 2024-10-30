#include "SizeType.hpp"
#include <istream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include "StringParseFunctions.hpp"

std::istream& novikov::operator>>(std::istream& in, SizeType& value)
{
  std::istream::sentry sentry(in);

  if (!sentry)
  {
    return in;
  }

  std::string temp;
  in >> temp;

  if (!containsOnlyNumbers(temp))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  size_t size = 0;

  try
  {
    size = std::stoul(temp);
  }
  catch (const std::invalid_argument&)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  value.size = size;
  return in;
}
