#include "compute_handler.hpp"
#include "pipe_communication.hpp"

void kravchenko::handleArea(int fdsFromUser, CalcMap& calcs)
{
  std::string calcName;
  CircleData data;
  size_t threads = 0;
  size_t tries = 0;
  pipePop(fdsFromUser, calcName);
  pipePop(fdsFromUser, data);
  pipePop(fdsFromUser, threads);
  pipePop(fdsFromUser, tries);
  calcs[calcName] = { false, 0.0 };
}
