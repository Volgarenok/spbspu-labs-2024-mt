#ifndef COMPUTE_HANDLER_HPP
#define COMPUTE_HANDLER_HPP

#include "commands.hpp"
#include "pipe_channel.hpp"

namespace kravchenko
{
  enum class QueryType
  {
    QUIT,
    AREA
  };

  void handleArea(PipeChannel& channel, CalcMap& calcs);
}

#endif