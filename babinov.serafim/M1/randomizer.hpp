#ifndef RANDOMIZER_HPP
#define RANDOMIZER_HPP
#include <random>

namespace babinov
{
  class Randomizer
  {
   public:
    Randomizer(size_t seed, double from, double to);
    double next();
   private:
    std::uniform_real_distribution< double > dist;
    std::default_random_engine gen;
  };
}

#endif
