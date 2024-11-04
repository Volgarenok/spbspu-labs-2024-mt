#include <iostream>

int main(int argc, char * argv[])
{
  if (argc < 2 || argc > 3)
  {
    std::cerr << "Invalid command line arguments number: " <<  argc << "\n";
    return 1;
  }
  size_t tries_number = 0;
  try
  {
    tries_number = std::stoull(argv[1]);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  size_t seed = 0;
  if (argc == 3)
  {
    try
    {
      seed = std::stoull(argv[2]);
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << "\n";
      return 3;
    }
  }
  return 0;
}
