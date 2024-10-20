#include "clicker.hpp"

klyukin::Clicker::Clicker():
  start_(std::chrono::high_resolution_clock::now())
{}

double klyukin::Clicker::millisec() const
{
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::microseconds;
  auto t = high_resolution_clock::now();
  return double(duration_cast< microseconds >(t - start_).count()) / 1000;
}
