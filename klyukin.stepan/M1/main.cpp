#include <iostream>
#include <vector>
#include <numeric>
#include <thread>
#include <cstdlib>
#include "clicker.hh"


// value_t sum_data(c_it_t begin, c_it_t end)
// {
//   value_t res = value_t{0};
//   for (c_it_t c = begin; c != end; c++)
//   {
//     res += *c + std::rand() % 2;
//   }
//   return res;
// }

double getRandomCoordinate() {
  return (double)(rand()) / (double)(RAND_MAX) - 0.5;
}

void countHits(int tries, std::vector< int >::iterator res) {
  for (int i = 0; i < tries; i++) {
    double x = getRandomCoordinate();
    double y = getRandomCoordinate();
    *res += (x * x + y * y < 0.25);
  }
}

double getArea(int tries, int radius, int threads) {
  std::vector< std::thread > ths;
  ths.reserve(threads);
  std::vector< int > results(threads, 0);

  int per_th = tries / threads;
  int last_th = per_th + tries % threads;
  for (int i = 0; i < threads - 1; i++) {
    ths.emplace_back(countHits, per_th, results.begin() + i);
  }
  countHits(last_th, results.begin() + (threads - 1));
  for (auto && th: ths)
  {
    th.join();
  }
  // std::cout << std::accumulate(results.cbegin(), results.cend(), 0) << '\n';
  double prob = double(std::accumulate(results.cbegin(), results.cend(), 0)) / tries;
  return 4 * radius * radius * prob;
}

void readTasksWriteResults(int tries, std::istream& in, std::ostream& out) {
  int radius, threads;
  in >> radius >> threads;
  while (!in.eof()) {
    if (radius < 1 || threads < 1) {
      throw std::logic_error("radius or n o t n p n");
    }
    {
      mtt::Clicker cl;
      double area = getArea(tries, radius, threads);
      double time = cl.millisec();
      out << time << ' ' << area << '\n'; // TODO format
    }
    in >> radius >> threads;
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "tries not given\n";
    return 1;
  }
  int tries = std::atoi(argv[1]);
  if (tries < 1) {
    std::cerr << "tries not positive number\n";
    return 2;
  }

  int seed = 0;
  if (argc > 2) {
    seed = std::atoi(argv[2]);
    if (seed < 0) {
      std::cerr << "seed negative\n";
      return 3;
    }
  }
  std::srand(seed);

  try {
    readTasksWriteResults(tries, std::cin, std::cout);
  } catch (const std::logic_error& error) {
    std::cerr << error.what() << '\n';
    return 4;
  }

  // for (int i = 0; i < tries; i++) {
  //   std::cout << getRandomCoordinate() << '\n';
  // }
  // for (int i = 0; i < tries; i++) {
  //   double x = getRandomCoordinate();
  //   double y = getRandomCoordinate();
  //   std::cout << (x * x + y * y < 0.25) << '\n';
  // }
  return 0;
}
