#include "pts_in_circle_counter.hpp"

void pts_in_circle_counter(size_t radius, size_t iters_nmb, lrnd32 generator, std::vector< size_t >::iterator it)
{
  double x{}, y{}, r = static_cast<double>(radius);
  size_t counter{};
  std::uniform_real_distribution< double > distr(-static_cast<double>(radius), static_cast<double>(radius));
  for (; iters_nmb; --iters_nmb)
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
