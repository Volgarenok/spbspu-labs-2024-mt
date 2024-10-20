#include <chrono>
#include <exception>
#include <iomanip>
#include <iostream>
#include "StreamGuard.hpp"
#include "get_area.hpp"

int main(int argc, char* argv[])
{
  if (argc > 3 || argc == 1)
  {
    std::cerr << "Input error - number of parameters\n";
    return 1;
  }
  using namespace novokhatskiy;
  size_t tries{};
  size_t seed{};
  try
  {
    if (argc == 3)
    {
      if (std::stoi(argv[1]) < 0 || std::stoi(argv[2]) < 0)
      {
        throw std::invalid_argument("Parameters can't be negative\n");
      }
      tries = std::stoull(argv[1]);
      seed = std::stoull(argv[2]);
    }
    else
    {
      tries = std::stoull(argv[1]);
    }
    size_t radius, countThreads{};
    std::minstd_rand randomDevice(seed);
    StreamGuard guard(std::cout);
    std::cout << std::setprecision(3) << std::fixed;
    while (!std::cin.eof())
    {
      std::cin >> radius >> countThreads;
      if (radius <= 0 || countThreads <= 0)
      {
        std::cerr << "Radius and amount of threads can't be negative or zero\n";
        return 1;
      }
      auto init = std::chrono::high_resolution_clock::now();
      auto square = processMK(radius, countThreads, tries,randomDevice);
      auto end = std::chrono::high_resolution_clock::now();
      auto time = static_cast< double >(std::chrono::duration_cast< std::chrono::microseconds >(end - init).count());
      std::cout << time / 1000.0 << ' ' << square << '\n';
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
