#include <iostream>
#include <cstddef>
#include <string>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <limits>
#include "CircleInput.hpp"

int main(int argc, char* argv[])
{
  if (argc == 1 || argc > 3)
  {
    std::cerr << "Некорректное кол-во параметров!\n";
    return -1;
  }

  ptrdiff_t input_tries = 0;
  ptrdiff_t input_seed = 0;

  try
  {
    input_tries = std::stol(argv[1]);

    if (argc == 3)
    {
      input_seed = std::stol(argv[2]);
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << "Некорректные параметры!\n";
    return -1;
  }

  if (input_tries < 1 || input_seed < 0)
  {
    std::cerr << "Некорректные значения параметров!\n";
    return -1;
  }

  size_t tries = input_tries;
  size_t seed = input_seed;

  using namespace novikov;
  std::vector< CircleInput > circles;

  using input_it_t = std::istream_iterator< CircleInput >;
  std::copy(input_it_t(std::cin), input_it_t(), std::back_inserter(circles));

  if (!std::cin.eof())
  {
    std::cerr << "Некорректные входные данные!\n";
    return -1;
  }

  std::cout << tries << " " << seed << "\n";
}
