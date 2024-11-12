#include "Timer.hpp"

novikov::Timer::Timer():
  start_(std::chrono::high_resolution_clock::now())
{}

double novikov::Timer::getElapsedTime() const
{
  auto t = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast< std::chrono::nanoseconds >(t - start_).count() / 1e6;
}
