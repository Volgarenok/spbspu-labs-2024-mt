#ifndef SET_HPP
#define SET_HPP
#include <map>
#include "circle.hpp"

namespace piyavkin
{
  class Set
  {
  public:
    void insert(const std::string& name, const Circle& c);
    rectangle_t getFrame() const;
  private:
    std::map< std::string, Circle > set_;
    rectangle_t rectangle_;
    friend std::ostream& operator<<(std::ostream& out, const Set& s);
  };
  std::ostream& operator<<(std::ostream& out, const Set& s);
}
#endif