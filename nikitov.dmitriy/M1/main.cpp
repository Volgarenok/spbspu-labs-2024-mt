#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

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
    std::cerr << "Error: Wrong command line arguments" << '\n';
    return 1;
  }

  if (seed < 0 || tries <= 0)
  {
    std::cerr << "Error: Wrong seed or tries" << '\n';
    return 1;
  }

  int radius = 0;
  int numberOfThreads = 0;
  std::cout << std::fixed << std::setprecision(4);
  while (std::cin >> radius && std::cin >> numberOfThreads)
  {
    if (radius <= 0 || numberOfThreads <= 0)
    {
      std::cerr << "Error: Wrong radius or number of threads" << '\n';
      return 2;
    }
    auto begin = std::chrono::high_resolution_clock::now();
    double square = 0;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast< std::chrono::milliseconds >(end - begin).count() << ' ' << square << '\n';
  }

  return 0;
}