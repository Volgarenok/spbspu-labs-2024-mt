#include "iostream"
#include "utility"
#include "random"
#include "chrono"

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

double getSquare(int& r)
{
  constexpr double PI = 3.1415926535;
  return PI * r * r;
}

using Point = std::pair< double, double >;

void processMK(int& r, int& threads, size_t& tries, double & seed, std::random_device& randomDevice)
{
  double square = getSquare(r);
  std::cout << "Real square: " << square << '\n';
  std::uniform_real_distribution< double > randomDouble(seed, 10.0);
  for (size_t i = 0; i < 10; ++i)
  {
    double num = randomDouble(randomDevice);
    std::cout << num << '\n';
  }
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
  int radius, countThreads{};
  std::random_device randomDevice;
  std::cout << tries << '\t' << seed << '\n';
  double init{0}, end{0};
  Clicker cl;
  init = cl.getTime();
  std::cout << "start - " << init << '\n';
  for (int i = 0; i < 100000000; ++i)
  {

  }
  end = cl.getTime();
  std::cout << "End - " << end << '\n';
  /*while (!std::cin.eof())
  {
    std::cout << "Enter data:\n>";
    std::cin >> radius >> countThreads;
    if (radius < 0 || countThreads < 0)
    {
      std::cerr << "Radius and amount of threads can't be negative\n";
      continue;
    }
    std::cout << radius << '\t' << countThreads << '\n';
  }*/
}
