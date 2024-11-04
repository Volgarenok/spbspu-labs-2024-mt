#include <iostream>
#include <chrono>
#include "calculate_circle_square.hpp"

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
    if (tries_number == 0)
    {
      throw std::logic_error("Tries number cannot be zero");
    }
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
  size_t radius = 0;
  size_t threads_number = 0;
  while (std::cin >> radius >> threads_number)
  {
    if (!radius || !threads_number)
    {
      std::cerr << "Wrong circle radius or threads number\n";
      return 4;
    }
    auto start = std::chrono::high_resolution_clock.now();
    double result = erohin::calculateCircleSquare(radius, threads_number, tries_number);
    auto end = std::chrono::high_resolution_clock.now();
    auto time = std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count();
    std::cout << std::fixed << std::setprecision(3);
    std::cout << static_cast< double >(time) << " " << result << "\n";
  }
  if (!std.cin)
  {
    std::cerr << "Wrong circle radius or threads number\n";
    return 4;
  }
  return 0;
}
