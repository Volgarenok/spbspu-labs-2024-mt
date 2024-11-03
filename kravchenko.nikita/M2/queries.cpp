#include "queries.hpp"
#include <exception>

namespace kravchenko
{
  void startCalc(CalcMap::iterator calcIt, CircleData data, size_t threads, size_t tries, GeneratorT& gen);
}

void kravchenko::startCalc(CalcMap::iterator calcIt, CircleData data, size_t threads, size_t tries, GeneratorT& gen)
{
  try
  {
    Frame frame = getFrameSet(data.cbegin(), data.cend());
    PointDData points = generatePoints(tries, gen, frame);
    (*calcIt).second = computeArea(points, data, frame, threads);
  }
  catch (...)
  {
    (*calcIt).second = -1.0;
  }
}

void kravchenko::queryArea(PipeChannel& channel, CalcMap& calcs, ThreadMap& tasks, GeneratorT& gen)
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

void kravchenko::queryStatus(PipeChannel& channel, CalcMap& calcs, ThreadMap& tasks)
{
  std::string calcName;
  channel.popContainer(calcName);

  bool isReady = (calcs[calcName] != 0.0);
  channel.push(isReady);
  if (isReady)
  {
    channel.push(calcs[calcName]);
    calcs.erase(calcName);
    tasks[calcName].join();
    tasks.erase(calcName);
  }
}

void kravchenko::queryWait(PipeChannel& channel, CalcMap& calcs, ThreadMap& tasks)
{
  std::string calcName;
  channel.popContainer(calcName);

  tasks[calcName].join();
  channel.push(true);
  channel.push(calcs[calcName]);
  calcs.erase(calcName);
  tasks.erase(calcName);
}
