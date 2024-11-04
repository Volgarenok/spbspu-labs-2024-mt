#include "calculate_circle_square.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <thread>
#include "generate_random_point.hpp"

namespace erohin
{
  bool isPointInCircle(point_t point, size_t radius)
  {
    return (point.x * point.x + point.y * point.y) <= (radius * radius);
  }
}

void erohin::countRandomPoints(size_t number, size_t radius, std::minstd_rand & generator, size_t & result)
{
  std::vector< point_t > points(number);
  auto random_point_generator = std::bind(generateRandomPoint, std::ref(generator), radius);
  std::generate(points.begin(), points.end(), random_point_generator);
  std::function< bool(point_t) > point_predicate;
  {
    using namespace std::placeholders;
    point_predicate = std::bind(isPointInCircle, _1, radius);
  }
  result = std::count_if(points.cbegin(), points.cend(), point_predicate);
}

double erohin::calculateCircleSquare(size_t radius, size_t threads_number, size_t tries_number, size_t seed)
{
  std::vector< std::thread > threads(threads_number - 1);
  std::vector< size_t > results(threads_number);
  size_t thread_capacity = tries_number / threads_number;
  std::minstd_rand generator(seed);
  for (size_t i = 0; i < threads_number - 1; ++i)
  {
    threads.emplace_back(countRandomPoints, thread_capacity, radius, std::ref(generator), std::ref(results[i]));
  }
  countRandomPoints(thread_capacity + tries_number % threads_number, radius, generator, results[threads_number - 1]);
  for (auto && cur_thread: threads)
  {
    cur_thread.join();
  }
  size_t filled_points_number = std::accumulate(results.cbegin(), results.cend(), 0);
  double square = static_cast< double >(filled_points_number) / tries_number * 4 * radius * radius;
  return square;
}
