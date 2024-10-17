#include "iostream"
#include "utility"
#include "random"
#include "chrono"
#include "thread"

using Point = std::pair< double, double >;

class Clicker
{
public:
  Clicker():
    start_(std::chrono::high_resolution_clock::now())
  {}
  double getTime() const
  {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    auto t = high_resolution_clock::now();
    return duration_cast< milliseconds >(t - start_).count();
  }
private:
  std::chrono::time_point< std::chrono::system_clock > start_;
};

Point createPoint(double& seed, std::random_device& randomDevice)
{
  std::uniform_real_distribution< double > randomDouble(seed, seed + 15.0);
  Point p;
  auto tmp = randomDouble(randomDevice);
  p.first = tmp;
  tmp = randomDouble(randomDevice);
  p.second = tmp;
  return p;
}

double getSquare(int& r)
{
  constexpr double PI = 3.14159;
  return PI * r * r;
  //return 4 * r * r;
}

void processMK(int& r, int& threads, size_t& tries, double &seed, std::random_device& randomDevice)
{
  size_t insidePoints{0};
  Clicker cl;
  std::cout << "Real sq - " << getSquare(r) << '\n';
  for (size_t i = 0; i < tries; ++i)
  {
    Point p = createPoint(seed, randomDevice);
    if ((p.first * p.first) + (p.second * p.second) <= (r * r))
    {
      insidePoints++;
    }
  }
  double time = cl.getTime();
  double ratio = static_cast< double >(insidePoints / tries);
  double sq = ratio * 4 * r * r;
  std::cout << sq << " " << time;
}

int main(int argc, char* argv[])
{
  if (argc > 3 || argc == 1)
  {
    std::cerr << "Input error - number of parameters\n";
    return 1;
  }
  size_t tries{};
  double seed{};
  if (argc == 3)
  {
    if (std::stoi(argv[1]) < 0 || std::stod(argv[2]) < 0)
    {
      std::cerr << "Parameters can't be negative\n";
      return 1;
    }
    tries = std::stoull(argv[1]);
    seed = std::stod(argv[2]);
  }
  else
  {
    tries = std::stoull(argv[1]);
  }
  const size_t myThreads = std::thread::hardware_concurrency();
  std::vector< std::thread > ths;
  ths.reserve(myThreads);
  
  int radius, countThreads{};
  std::random_device randomDevice;
  std::cout << tries << '\t' << seed << '\n';
  while (!std::cin.eof())
  {
    std::cout << "Enter data:\n>";
    std::cin >> radius >> countThreads;
    if (radius < 0 || countThreads < 0)
    {
      std::cerr << "Radius and amount of threads can't be negative\n";
      continue;
    }
    processMK(radius, countThreads, tries, seed, randomDevice);
    std::cout << '\n';
  }
}
