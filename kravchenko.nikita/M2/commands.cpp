#include "commands.hpp"
#include <exception>
#include "compute_handler.hpp"
#include "pipe_communication.hpp"

void kravchenko::cmdCircle(CircleMap& circles, std::istream& in, std::ostream&)
{
  std::string name;
  Circle c;
  in >> name >> c;
  if (!in)
  {
    throw std::invalid_argument("<INVALID INPUT>");
  }
  if (circles.find(name) != circles.end())
  {
    throw std::invalid_argument("<CIRCLE ALREADY EXISTS>");
  }
  circles[name] = c;
}

void kravchenko::cmdSet(CircleSetMap& sets, const CircleMap& circles, std::istream& in, std::ostream&)
{
  std::string setName;
  size_t size = 0;
  in >> setName >> size;
  if (!in)
  {
    throw std::invalid_argument("<INVALID INPUT>");
  }
  if (sets.find(setName) != sets.end())
  {
    throw std::invalid_argument("<SET ALREADY EXISTS>");
  }
  if (size < 1)
  {
    throw std::invalid_argument("<INVALID SIZE>");
  }
  CircleWrappedData data;
  data.reserve(size);
  for (size_t i = 0; i < size; ++i)
  {
    std::string circleName;
    in >> circleName;
    auto foundIt = circles.find(circleName);
    if (foundIt == circles.end())
    {
      throw std::invalid_argument("<CIRCLE " + circleName + " NOT FOUND>");
    }
    data.push_back(*foundIt);
  }
  sets[setName] = data;
}

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