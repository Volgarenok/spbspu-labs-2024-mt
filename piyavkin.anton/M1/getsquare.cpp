#include "getsquare.hpp"

double piyavkin::getSquare(const std::vector< std::pair< double, double > >& points, size_t r, size_t countThreads)
{
  return points[0].first * r * countThreads;
}