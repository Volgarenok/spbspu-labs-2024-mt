#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include "lrnd32.hpp"
#include "monte_carlo.hpp"

int main(int argc, char** argv)
{
  size_t iterations{};
  size_t seed{};
  try {
    switch (argc)
    {
    case 3:
      if (argv[2][0] == '-')
      {
        throw std::invalid_argument("");
      }
      seed = std::strtoull(argv[2], nullptr, 10);
    case 2:
      if (argv[1][0] == '-')
      {
        throw std::invalid_argument("");
      }
      iterations = std::strtoull(argv[1], nullptr, 10);
      break;
    default:
      std::cerr << "Invalid number of arguments\n";
      return 1;
    }
  }
  catch (const std::exception&)
  {
    std::cerr << "Failed to convert arguments to ull\n";
    return 1;
  }
  if (!iterations)
  {
    std::cerr << "Iterations number unable to be zero\n";
  }

  std::string r, thrds;
  std::cout << std::setprecision(3) << std::fixed;
  std::chrono::time_point< std::chrono::high_resolution_clock> start_{};
  try
  {
    while (std::cin >> r >> thrds)
    {
      if (!std::cin || r[0]=='-' || thrds[0]=='-')
      {
        std::cerr << "Invalid conditions\n";
        return 1;
      }
      unsigned long long radius = std::stoull(r);
      unsigned long long threads = std::stoull(thrds);
      zaitsev::lrnd32 generator(seed);
      auto start = std::chrono::high_resolution_clock::now();
      double area = zaitsev::calc_area(radius, iterations, threads, generator);
      auto end = std::chrono::high_resolution_clock::now();
      std::cout << std::chrono::duration_cast< std::chrono::microseconds >(end - start).count() /1000.0 << " " << area << "\n";
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }
  return 0;
}
