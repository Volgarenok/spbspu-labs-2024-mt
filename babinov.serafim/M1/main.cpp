#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

#include "circles.hpp"

bool isValidData(babinov::CircleData data)
{
  return (data.radius > 0) && (data.nThreads > 0);
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Too few arguments" << '\n';
    return 1;
  }
  int tries = 0;
  int seed = 0;
  try
  {
    tries = std::stoi(argv[1]);
    if (argc > 2)
    {
      seed = std::stoi(argv[2]);
    }
    if ((tries <= 0) || (seed < 0))
    {
      throw std::invalid_argument("");
    }
  }
  catch (const std::invalid_argument&)
  {
    std::cerr << "Invalid arguments" << '\n';
    return 1;
  }

  using namespace babinov;
  using input_it_t = std::istream_iterator< CircleData >;
  std::vector< CircleData > data;
//  while (!std::cin.eof())
//  {
//    std::copy_if(input_it_t(std::cin), input_it_t(), std::back_inserter(data), isValidData);
//  }
  return 0;
}
