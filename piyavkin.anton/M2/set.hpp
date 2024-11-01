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
    rectangle_t getFrame() const;
    std::string getStr() const;
    bool isInside(const std::pair< double, double >& p) const;
  private:
    std::vector< Circle > set_;
    rectangle_t rectangle_;
    friend std::ostream& operator<<(std::ostream& out, const Set& s);
  };
  std::ostream& operator<<(std::ostream& out, const Set& s);
  Set parse(const std::string& str);
}
#endif