#include <iostream>
#include <random>
#include <iomanip>
#include <cstdlib>
#include<string>
#include "lrnd32.hpp"

int main(int argc, char** argv)
{
  size_t iterations{};
  size_t seed{};
  try {
    switch (argc)
    {
    case 3:
      if (argv[2][0] == '-')
      {
        throw std::invalid_argument("");
      }
      seed = std::strtoull(argv[2], nullptr, 10);
    case 2:
      if (argv[1][0] == '-')
      {
        throw std::invalid_argument("");
      }
      iterations = std::strtoull(argv[1], nullptr, 10);
      break;
    default:
      std::cerr << "Invalid number of arguments\n";
      return 1;
    }
  }
  catch (const std::exception&)
  {
    std::cerr << "Failed to convert arguments to ull\n";
    return 1;
  }

  if (!iterations)
  {
    std::cerr << "Iterations number unable to be zero\n";
  }
  return 0;
}
