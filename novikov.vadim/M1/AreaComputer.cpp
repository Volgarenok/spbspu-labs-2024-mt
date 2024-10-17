#include "AreaComputer.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <thread>
#include <random>
#include <functional>
#include "Timer.hpp"

novikov::AreaComputer::AreaComputer(size_t tries, size_t seed):
  tries_(tries),
  seed_(seed)
{}

novikov::CircleOutput novikov::AreaComputer::operator()(const CircleInput& circle)
{
  std::vector< std::thread > threads;
  threads.reserve(circle.thread_count - 1);

  using point_t = std::pair< double, double >;
  std::vector< point_t > values(tries_, {0.0, 0.0});
  hits_.assign(circle.thread_count, 0);

  size_t per_thread = tries_ / circle.thread_count;
  auto value_it = values.begin();

  Timer timer;
  double start = timer.getElapsedTime();

  for (size_t i = 0; i < circle.thread_count - 1; ++i)
  {
    auto end = value_it + per_thread;
    threads.emplace_back(&AreaComputer::generatePoints, this, value_it, end, circle.radius, i);
    value_it = end;
  }

  generatePoints(value_it, value_it + per_thread + tries_ % circle.thread_count, circle.radius, hits_.size() - 1);

  for (auto&& th : threads)
  {
      th.join();
  }

  double total_time = timer.getElapsedTime() - start;
  double total_area = 4 * std::pow(circle.radius, 2) * std::accumulate(hits_.cbegin(), hits_.cend(), 0) / tries_;

  return {total_time, total_area};
}

novikov::AreaComputer::point_t novikov::AreaComputer::generatePoint(std::mt19937& generator, double radius, size_t hits_index)
{
  std::uniform_real_distribution<double> distribution(-radius, radius);

  double x = distribution(generator);
  double y = distribution(generator);

  if (std::hypot(x, y) < radius)
  {
    ++hits_[hits_index];
  }

  return {x, y};
}

void novikov::AreaComputer::generatePoints(it_t begin, it_t end, double radius, size_t hits_index)
{
  std::mt19937 randomizer(seed_);
  auto generator = std::bind(&AreaComputer::generatePoint, this, std::ref(randomizer), radius, hits_index);
  std::generate(begin, end, generator);
}
