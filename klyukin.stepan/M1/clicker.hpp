#ifndef CLICKER_HH
#define CLICKER_HH
#include <chrono>

namespace klyukin {
  class Clicker {
   public:
    Clicker();
    double millisec() const;
   private:
    std::chrono::time_point< std::chrono::system_clock > start_;
  };
}
#endif
