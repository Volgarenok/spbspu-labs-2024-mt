#ifndef LRND32
#define LRND32
#include <bitset>
#include <array>

using poly512 = std::bitset< 512 >;
using poly256 = std::bitset< 256 >;

class lrnd32
{
public:
  lrnd32(size_t seed);
  unsigned int generate_next();
  void set_start_value(size_t seed);

private:
  static const poly512 mod_poly512;
  static const poly256 mod_poly256;
  static const std::array< poly512, 256 > deg2;
  poly256 poly;
  size_t basic_offset_;
  unsigned int generated_number_;
};

#endif
