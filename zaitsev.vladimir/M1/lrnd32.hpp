#ifndef LRND32
#define LRND32
#include <bitset>
#include <array>

using poly510 = std::bitset< 510 >;
class lrnd32
{
public:
  lrnd32(size_t seed);
  unsigned int generate_next();
  void set_start_value(size_t seed);

private:
  static const poly510 mod_poly;
  static const std::array< poly510, 256 > deg2;
  poly510 poly;
  size_t basic_offset_;
  unsigned int generated_number_;
};

#endif
