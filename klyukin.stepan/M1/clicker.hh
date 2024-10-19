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
      using std::chrono::milliseconds;
      auto t = high_resolution_clock::now();
      return duration_cast< milliseconds >(t - start_).count();
    }

   private:
    std::chrono::time_point< std::chrono::system_clock > start_;
  };
}
#endif
