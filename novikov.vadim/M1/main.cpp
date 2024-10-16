#include <iostream>
#include <cstddef>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[])
{
  if (argc == 1 || argc > 3)
  {
    std::cerr << "Неверное кол-во параметров!\n";
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
    std::cerr << e.what() << "\n";
    return -1;
  }

  if (input_tries < 1 || input_seed < 0)
  {
    std::cerr << "Некорректные параметры!\n";
    return -1;
  }

  size_t tries = input_tries;
  size_t seed = input_seed;

  std::cout << tries << " " << seed << "\n";
}
