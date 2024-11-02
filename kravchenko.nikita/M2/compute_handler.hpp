#ifndef COMPUTE_HANDLER_HPP
#define COMPUTE_HANDLER_HPP

#include <thread>
#include <unordered_map>
#include <utility>
#include "monte_carlo.hpp"
#include "pipe_channel.hpp"

namespace kravchenko
{
  using ThreadMap = std::unordered_map< std::string, std::thread >;
  using CalcMap = std::unordered_map< std::string, double >;

  enum QueryType
  {
    QUIT,
    AREA,
    STATUS,
    WAIT
  };

  void handleArea(PipeChannel& channel, CalcMap& calcs, ThreadMap& tasks, GeneratorT& gen);
  void handleStatus(PipeChannel& channel, CalcMap& calcs, ThreadMap& tasks);
  void handleWait(PipeChannel& channel, CalcMap& calcs, ThreadMap& tasks);
}

#endif