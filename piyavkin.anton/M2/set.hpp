#ifndef SET_HPP
#define SET_HPP
#include <vector>
#include "circle.hpp"

namespace piyavkin
{
  class Set
  {
  public:
    void insert(const Circle& c);
  private:
    std::vector< Circle > set_;
  };
}
#endif