#include "circle.hpp"

Circle::Circle(const std::string& name, const point_t& c, size_t r):
  name_(name),
  center_(c),
  radius_(r)
{}