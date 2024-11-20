#include "monte_carlo.hpp"
#include <thread>
#include <numeric>
#include <random>

void count_pts_in_circle(size_t radius, size_t iterations, zaitsev::lrnd32 generator, std::vector< size_t >::iterator it);

double zaitsev::calc_area(size_t radius, size_t iterations, size_t threads, lrnd32 generator)
{
  std::vector< size_t > counters(threads, 0);
  std::vector< std::thread >thrds;
  thrds.reserve(threads - 1);
  size_t iters_per_thread = iterations / threads;

  for (size_t i = 0; i < threads - 1; ++i)
  {
    thrds.emplace_back(count_pts_in_circle, radius, iters_per_thread, generator, counters.begin() + i);
    generator.discard(iterations);
  }
  count_pts_in_circle(radius, iters_per_thread + iterations % iters_per_thread, generator, counters.end() - 1);
  for (auto&& thrd : thrds)
  {
    thrd.join();
  }

  size_t counter = std::accumulate(counters.cbegin(), counters.cend(), 0);

  return static_cast< double >(counter) / iterations * radius * radius * 4;
}

void count_pts_in_circle(size_t radius, size_t iterations, zaitsev::lrnd32 generator, std::vector< size_t >::iterator it)
{
  double x{}, y{}, r = static_cast< double >(radius);
  size_t counter{};
  std::uniform_real_distribution< double > distr(-static_cast<double>(radius), static_cast<double>(radius));
  for (; iterations; --iterations)
  {
    x = distr(generator);
    y = distr(generator);
    if (x * x + y * y <= r * r)
    {
      ++counter;
    }
  }
  *it = counter;
  return;
}
