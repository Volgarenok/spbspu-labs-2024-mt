#include <iostream>
#include "lrnd32.hpp"
#include <random>

int main(int argc, char** argv)
{
  lrnd32 gen(41);
  size_t groups[64]{};
  unsigned int x = 67'108'864;
  std::mt19937 gn(41);
  for (size_t i = 0; i < 1e8; ++i)
  {
    ++groups[gen.generate_next() / x];
  }
  for (size_t i = 0; i < 64; ++i)
  {
    std::cout << i << "---" << groups[i] << '\n';
  }

  return 0;
}
