#include "compute_handler.hpp"
#include <exception>

void kravchenko::handleArea(PipeChannel& channel, CalcMap& calcs, ThreadMap& tasks, GeneratorT& gen)
{
  std::string calcName;
  CircleData data;
  size_t threads = 0;
  size_t tries = 0;
  channel.popContainer(calcName);
  channel.popContainer(data);
  channel.pop(threads);
  channel.pop(tries);
  auto it = calcs.insert({ calcName, 0.0 }).first;
  tasks[calcName] = std::thread(startCalc, it, data, threads, tries, std::ref(gen));
}

void kravchenko::startCalc(CalcMap::iterator calcIt, CircleData data, size_t threads, size_t tries, GeneratorT& gen)
{
  try
  {
    Frame frame = cmd::getFrameSet(data.cbegin(), data.cend());
    PointDData points = generatePoints(tries, gen, frame);
    (*calcIt).second = computeArea(points, data, frame, threads);
  }
  catch (const std::exception& e)
  {
    (*calcIt).second = -1.0;
  }
}