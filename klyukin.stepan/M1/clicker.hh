#ifndef CLICKER_HH
#define CLICKER_HH
#include <chrono>

namespace mtt
{
  class Clicker
  {
   public:
    Clicker():
     start_(std::chrono::high_resolution_clock::now())
    {}

    double millisec() const
    {
      using std::chrono::high_resolution_clock;
      using std::chrono::duration_cast;
      using std::chrono::microseconds;
      auto t = high_resolution_clock::now();
      return double(duration_cast< microseconds >(t - start_).count()) / 1000;
    }

   private:
    std::chrono::time_point< std::chrono::system_clock > start_;
  };
}
#endif
