#include "iostream"
#include "random"

double getSquare(int& r)
{
  constexpr double PI = 3.1415926535;
  return PI * r * r;
}

template < typename T >
void processMK(int& r, int& threads, size_t& ties, size_t& seed, T randomDevice)
{}

int main(int argc, char* argv[])
{
  if (argc > 3 || argc == 1)
  {
    std::cerr << "Input error - number of parameters\n";
    return 1;
  }
  size_t ties{};
  size_t seed{};
  if (argc == 3)
  {
    if (std::stoi(argv[1]) < 0 || std::stoi(argv[2]) < 0)
    {
      std::cerr << "Parameters can't be negative\n";
      return 1;
    }
    ties = std::stoull(argv[1]);
    seed = std::stoull(argv[2]);
  }
  else
  {
    ties = std::stoull(argv[1]);
  }
  int radius, countThreads{};
  std::random_device rand;
  std::cout << ties << '\t' << seed << '\n';
  while (!std::cin.eof())
  {
    std::cout << "Enter data: ";
    std::cin >> radius >> countThreads;
    if (radius < 0 || countThreads < 0)
    {
      std::cerr << "Radius and amount of threads can't be negative\n";
      continue;
    }
    std::cout << std::endl;
    std::cout << radius << '\t' << countThreads << '\n';
  }
}
