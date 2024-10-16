#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Too few arguments" << '\n';
    return 1;
  }
  size_t tries = std::strtoull(argv[1], nullptr, 10);
  if (tries == 0)
  {
    std::cerr << "Invalid tries number" << '\n';
    return 1;
  }
  size_t seed = 0;
  if (argc > 2)
  {
    seed = std::strtoull(argv[2], nullptr, 10);
  }
}
