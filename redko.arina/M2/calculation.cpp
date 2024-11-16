#include "calculation.hpp"

redko::Calculation::Calculation():
  result(0.0),
  started(false),
  completed(false),
  threads()
{};

bool redko::Calculation::isCalculated()
{
  return completed;
}

void redko::Calculation::start(set_it setIt, int threadsNum, long long triesNum, int seedValue)
{
  if (started)
  {
    throw std::logic_error("the calculation has already started");
  }
  started = true;
  threads.reserve(threadsNum);
  threads.emplace_back(calculateArea, std::ref(threads), setIt, threadsNum, triesNum, seedValue, std::ref(result), std::ref(completed));
}

double redko::Calculation::getResult()
{
  if (!completed)
  {
    throw std::logic_error("the calculation has not yet completed");
  }
  if (threads.begin()->joinable())
  {
    threads.begin()->join();
  }
  return result;
}

void redko::Calculation::wait()
{
  if (!threads.begin()->joinable())
  {
    throw std::logic_error("the calculation has already completed");
  }
  threads.begin()->join();
}
