#include <iostream>
#include <random>
#include "lrnd32.hpp"


int main(int argc, char** argv)
{
  lrnd32 gen(41);
  size_t groups[64]{};
  unsigned int x = 67'108'864;
  std::mt19937 gn(41);
  std::uniform_real_distribution<double> urd(-5, 5);
  for (size_t i = 0; i < 1e3; ++i)
  {
    //++groups[gen() / x];
    std::cout << urd(gen) << '\n';
  }
  /*for (size_t i = 0; i < 64; ++i)
  {
    std::cout << i << "---" << groups[i] << '\n';
  }*/
  return 0;
}
