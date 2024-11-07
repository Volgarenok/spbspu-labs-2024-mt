#include <iostream>
#include "lrnd32.hpp"


int main(int argc, char** argv)
{
  lrnd32 gen(41);//41

  for (size_t i = 0; i < 10; ++i)
  {
    std::cout<<gen.generate_next()<<"\n";
  }

  return 0;
}
