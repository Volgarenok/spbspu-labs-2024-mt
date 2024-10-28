#include "commands.hpp"
#include <exception>
#include "compute_handler.hpp"
#include "pipe_communication.hpp"

void kravchenko::cmdArea(int fdsToCompute, const CircleSetMap& sets, CalcMap& calcs, std::istream& in, std::ostream&)
{
  std::string calcName;
  std::string setName;
  size_t threads = 0;
  size_t tries = 0;
  in >> calcName >> setName >> threads >> tries;
  if (calcs.find(calcName) != calcs.end())
  {
    throw std::invalid_argument("<CALC ALREADY EXISTS>");
  }
  auto sendSetIt = sets.find(setName);
  if (sendSetIt == sets.cend())
  {
    throw std::invalid_argument("<INVALID SET-NAME>");
  }
  if (threads == 0 || tries == 0)
  {
    throw std::invalid_argument("<INVALID THREADS AND/OR TRIES>");
  }
  pipePush(fdsToCompute, QueryType::AREA);
  pipePush(fdsToCompute, calcName);
  pipePush(fdsToCompute, (*sendSetIt).second);
  pipePush(fdsToCompute, threads);
  pipePush(fdsToCompute, tries);
  calcs[calcName] = { false, 0.0 };
}