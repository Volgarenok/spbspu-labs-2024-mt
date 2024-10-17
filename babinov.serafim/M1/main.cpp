#include <iostream>
#include <stdexcept>
#include <string>

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
    if (tries <= 0)
    {
      throw std::invalid_argument("");
    }
    if (argc > 2)
    {
      seed = std::stoi(argv[2]);
    }
  }
  catch (const std::invalid_argument&)
  {
    std::cerr << "Invalid arguments" << '\n';
    return 1;
  }

}
