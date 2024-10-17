#include <iostream>

int main(int argc, char* argv[])
{
  int seed = 0;
  int tries = 0;
  if (argc == 2)
  {
    tries = std::stoi(argv[1]);
  }
  else if (argc == 3)
  {
    tries = std::stoi(argv[1]);
    seed = std::stoi(argv[2]);
  }
  else
  {
    std::cerr << "Error: Wrong command line arguments\n";
    return 1;
  }

  if (seed < 0 || tries <= 0)
  {
    std::cerr << "Error: Wrong seed or tries\n";
    return 1;
  }
}