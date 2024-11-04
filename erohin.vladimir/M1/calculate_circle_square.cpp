#include "calculate_circle_square.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <thread>
#include "generate_random_point.hpp"

void erohin::generatePoints(point_array_t & points, size_t limit, size_t seed)
{
  std::minstd_rand generator(seed);
  auto random_point_generator = std::bind(generateRandomPoint, std::ref(generator), limit);
  std::generate(points.begin(), points.end(), random_point_generator);
}

namespace erohin
{
  bool isPointInCircle(point_t point, size_t radius)
  {
    return (point.x * point.x + point.y * point.y) <= (radius * radius);
  }
}

void erohin::countPoints(const point_array_t & points, size_t index, size_t number, size_t radius, size_t & result)
{
  auto point_predicate = std::bind(isPointInCircle, std::placeholders::_1, radius);
  result = std::count_if(points.cbegin() + index, points.cbegin() + index + number, point_predicate);
}

double erohin::calculateCircleSquare(size_t radius, size_t threads_number, size_t tries_number, size_t seed)
{
  point_array_t points(tries_number);
  generatePoints(points, radius, seed);
  std::vector< std::thread > threads;
  threads.reserve(threads_number - 1);
  std::vector< size_t > results(threads_number);
  size_t thread_capacity = tries_number / threads_number;
  for (size_t i = 0; i < threads_number - 1; ++i)
  {
    threads.emplace_back(countPoints, points, i * thread_capacity, thread_capacity, radius, std::ref(results[i]));
  }
  size_t last_capacity = thread_capacity + tries_number % threads_number;
  countPoints(points, (threads_number - 1) * thread_capacity, last_capacity, radius, results[threads_number - 1]);
  for (auto && cur_thread: threads)
  {
    cur_thread.join();
  }
  size_t filled_points_number = std::accumulate(results.cbegin(), results.cend(), 0);
  double square = static_cast< double >(filled_points_number) / tries_number * 4 * radius * radius;
  return square;
}
