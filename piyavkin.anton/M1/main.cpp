#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[])
{
  if (argc > 3 || argc < 2)
  {
    std::cerr << "The number of command line arguments does not meet the requirements\n";
    return 1;
  }
  try
  {
    if (argv[1][0] == '-')
    {
      throw std::logic_error("The number of tests is not positive");
    }
    size_t tries = std::stoll(argv[1]);
    size_t seed = 0;
    if (tries == 0)
    {
      throw std::logic_error("The number of tests is not positive");
    }
    if (argc == 3)
    {
      if (argv[2][0] == '-')
      {
        throw std::logic_error("The initialization value of the generator is negative");
      }
      seed = std::stoll(argv[2]);
    }
    std::cout << tries << ' ' << seed << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
}