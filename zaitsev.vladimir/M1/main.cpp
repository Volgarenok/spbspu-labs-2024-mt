#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include "lrnd32.hpp"
#include "pts_in_circle_counter.hpp"

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

  unsigned long long radius{};
  unsigned long long threads{};
  std::cout << std::setprecision(3) << std::fixed;
  std::chrono::time_point< std::chrono::high_resolution_clock> start_{};
  try
  {
    while (std::cin >> radius >> threads)
    {
      if (!std::cin || !radius || !threads)
      {
        throw std::invalid_argument("Invalid conditions");
      }
      std::vector< size_t > counters(threads, 0);
      std::vector< std::thread >thrds;
      std::vector< lrnd32 >thrdss;
      thrds.reserve(threads - 1);
      size_t iters_per_thread = iterations / threads;
      lrnd32 basic_generator(seed);
      auto start = std::chrono::high_resolution_clock::now();

      for (size_t i = 0; i < threads - 1; ++i)
      {
        thrds.emplace_back(pts_in_circle_counter, radius, iters_per_thread, basic_generator, counters.begin() + i);
        basic_generator.discard(iterations);
      }
      pts_in_circle_counter(radius, iters_per_thread + iterations % iters_per_thread, basic_generator, counters.end() - 1);
      for (auto&& thrd : thrds)
      {
        thrd.join();
      }

      size_t counter = std::accumulate(counters.cbegin(), counters.cend(), 0);
      auto end = std::chrono::high_resolution_clock::now();
      auto lasts = std::chrono::duration_cast< std::chrono::microseconds >(end - start);
      std::cout << lasts.count()/1000.0 << " " << static_cast<double>(counter) / iterations * radius * radius * 4 << "\n";
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }

  return 0;
}
