#ifndef LRND32
#define LRND32
#include <bitset>
#include <array>

using poly512 = std::bitset< 512 >;
using poly256 = std::bitset< 256 >;

class lrnd32
{
public:
  using result_type = unsigned int;

  lrnd32();
  lrnd32(lrnd32&&) = delete;
  lrnd32(const lrnd32&) = default;
  explicit lrnd32(result_type seed);
  ~lrnd32() = default;

  static unsigned int max();
  static unsigned int min();
  result_type operator()();
  void seed(result_type seed);

private:
  static const size_t basic_offset_;
  static const poly512 mod_poly512;
  static const poly256 mod_poly256;
  static const std::array< poly512, 256 > deg2;
  poly256 poly;
  result_type generated_number_;
};

#endif
