#ifndef COMPUTE_HANDLER_HPP
#define COMPUTE_HANDLER_HPP

#include <random>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>
#include "circle.hpp"
#include "commands.hpp"
#include "monte_carlo.hpp"
#include "pipe_channel.hpp"

namespace kravchenko
{
  using ThreadMap = std::unordered_map< std::string, std::thread >;
  enum class QueryType
  {
    QUIT,
    AREA,
    STATUS
  };

  void handleArea(PipeChannel& channel, CalcMap& calcs, ThreadMap& tasks, GeneratorT& gen);
  void handleStatus(PipeChannel& channel, CalcMap& calcs, ThreadMap& tasks);
  void startCalc(CalcMap::iterator calcIt, CircleData data, size_t threads, size_t tries, GeneratorT& gen);
}

#endif