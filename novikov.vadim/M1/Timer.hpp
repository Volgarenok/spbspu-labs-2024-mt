#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

namespace novikov
{
  class Timer
  {
  public:

    Timer();
    double getElapsedTime() const;

  private:

    std::chrono::time_point< std::chrono::system_clock > start_;
  };
}
#endif
