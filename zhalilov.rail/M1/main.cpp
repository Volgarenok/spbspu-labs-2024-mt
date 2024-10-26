#include <chrono>
#include <iomanip>
#include <iostream>

#include "calculateSquare.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2 && argc != 3)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  size_t iterations = 0;
  size_t seed = 0;
  try
  {
    iterations = std::stoull(argv[1]);
    if (argc == 3)
    {
      seed = std::stoull(argv[2]);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  size_t radius = 0;
  size_t threads = 0;
  std::cout << std::setprecision(3) << std::fixed;
  while (std::cin >> radius >> threads)
  {
    auto start = std::chrono::high_resolution_clock::now();
    double square = zhalilov::calcCircleSquare(radius, threads, iterations, seed);
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count();
    std::cout << time << ' ' << square << '\n';
  }
  if (!std::cin)
  {
    std::cerr << "Invalid input\n";
    return 1;
  }
}
