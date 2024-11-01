#include "compute_handler.hpp"

void kravchenko::handleArea(PipeChannel& channel, CalcMap& calcs)
{
  std::string calcName;
  CircleWrappedData data;
  size_t threads = 0;
  size_t tries = 0;
  channel.pop(calcName); // TODO
  channel.pop(data);     // TODO
  channel.pop(threads);
  channel.pop(tries);
  // TODO
  calcs[calcName] = { false, 0.0 };
}
