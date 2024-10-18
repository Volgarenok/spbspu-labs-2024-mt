#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <random>

namespace babinov
{
  class Generator
  {
   public:
    Generator(size_t seed, double from, double to);
    double next();
   private:
    std::uniform_real_distribution< double > dist;
    std::default_random_engine gen;
  };
}

#endif
