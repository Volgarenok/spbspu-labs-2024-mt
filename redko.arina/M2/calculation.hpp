#ifndef CALCULATION_HPP
#define CALCULATION_HPP
#include "setProcessing.hpp"

namespace redko
{
  class Calculation
  {
  public:
    Calculation();

    bool isCalculated();
    void start(set_it set, int threadsNum, long long triesNum, int seedValue);
    double getResult();
    void wait();

  private:
    double result;
    bool started;
    bool completed;
    std::vector< std::thread > threads;
  };
}

#endif
