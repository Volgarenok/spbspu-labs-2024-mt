#ifndef LRND32
#define LRND32
#include <bitset>
#include <cstddef>

namespace zaitsev
{
  using poly512 = std::bitset< 512 >;
  using poly256 = std::bitset< 256 >;

  class lrnd32
  {
  public:
    using result_type = unsigned int;

    lrnd32();
    lrnd32(lrnd32&&) = default;
    lrnd32(const lrnd32&) = default;
    explicit lrnd32(size_t seed);
    ~lrnd32() = default;

    static unsigned int max() noexcept;
    static unsigned int min() noexcept;
    result_type operator()() noexcept;
    result_type operator()(bool) noexcept;
    void seed(size_t seed);
    void discard(size_t seed);

  private:
    static constexpr size_t basic_offset_ = 183758644ull;
    static const poly512 mod_poly512_;
    static const poly256 mod_poly256_;
    static const unsigned long long mod_poly256_ull_[4];
    static const std::array< poly512, 256 > deg2_;
    poly256 poly_;
    unsigned long long poly_ull_[4];
    result_type generated_number_;
  };
}
#endif
