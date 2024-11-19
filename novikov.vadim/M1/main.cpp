#include <iostream>
#include <cstddef>
#include <string>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <algorithm>
#include "AreaComputer.hpp"
#include "StringFunctions.hpp"

int main(int argc, char* argv[])
{
  if (argc == 1 || argc > 3)
  {
    std::cerr << "Некорректное кол-во параметров!\n";
    return -1;
  }

  size_t tries = 0;
  size_t seed = 0;

  try
  { 
    using namespace novikov;
    tries = parseSizeType(argv[1]);

    if (argc == 3)
    {
      seed = parseSizeType(argv[2]);
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return -1;
  }

  if (tries == 0)
  {
    std::cerr << "Некорректные значения параметров!\n";
    return -1;
  }

  using namespace novikov;
  std::vector< CircleInput > circles;

  using input_it_t = std::istream_iterator< CircleInput >;
  std::copy(input_it_t(std::cin), input_it_t(), std::back_inserter(circles));

  if (!std::cin.eof())
  {
    std::cerr << "Некорректные входные данные!\n";
    return -1;
  }

  using output_it_t = std::ostream_iterator< CircleOutput >;
  std::transform(circles.cbegin(), circles.cend(), output_it_t(std::cout), AreaComputer(tries, seed));
}
