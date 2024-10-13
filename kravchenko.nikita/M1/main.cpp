#include <iostream>
#include <stdexcept>
#include <string>

size_t getArgument(const char* arg)
{
  if (arg[0] == '-')
  {
    throw std::logic_error("Invalid input");
  }
  return std::stoull(arg);
}

int main(int argc, char* argv[])
{
  if (argc < 2 || 3 < argc)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }
  size_t tries = 0;
  size_t seed = 0;
  try
  {
    tries = getArgument(argv[1]);
    if (tries == 0)
    {
      throw std::logic_error("Invalid input");
    }
    if (argc == 3)
    {
      seed = getArgument(argv[2]);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}