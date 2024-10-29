#ifndef SIZE_TYPE_HPP
#define SIZE_TYPE_HPP

#include <iosfwd>
#include <cstddef>

namespace novikov
{
  struct SizeType
  {
    size_t size;
  };

  std::istream& operator>>(std::istream& in, SizeType& value);
}

#endif
