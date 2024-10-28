#ifndef COMPUTE_HANDLER_HPP
#define COMPUTE_HANDLER_HPP

#include "commands.hpp"

namespace kravchenko
{
  enum class QueryType
  {
    QUIT,
    AREA
  };

  void handleArea(int fdsFromUser, CalcMap& calcs);
}

#endif