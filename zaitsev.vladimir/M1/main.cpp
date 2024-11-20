#include <iostream>
#include <random>
#include "lrnd32.hpp"


int main(int argc, char** argv)
{
  lrnd32 gen(41);
  lrnd32 gen2(41);
  gen2.discard(10);
  size_t groups[64]{};
  unsigned int x = 67'108'864;
  std::mt19937 gn(41);
  std::uniform_real_distribution<double> urd(-5, 5);
  for (size_t i = 0; i < 20; ++i)
  {
    std::cout<<i<<"  " << gen() << '\n';
  }
  std::cout << "\n\n";
  for (size_t i = 0; i < 10; ++i)
  {
    std::cout << i + 10 << "  " << gen2() << '\n';
  }
  /*for (size_t i = 0; i < 64; ++i)
  {
    std::cout << i << "---" << groups[i] << '\n';
  }*/
  return 0;
}
