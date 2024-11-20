#include "lrnd32.hpp"
#include <bitset>
#include <array>

using poly512 = std::bitset< 512 >;
using poly256 = std::bitset< 256 >;

template < size_t N >
std::bitset< N > form_mod_poly() noexcept
{
  static_assert(N >= 256, "Invalid poly size, size must be 256 or greater");
  std::bitset< N > mod_poly{};
  mod_poly[0] = 1;
  mod_poly[3] = 1;
  mod_poly[7] = 1;
  mod_poly[31] = 1;
  mod_poly[255] = 1;
  return mod_poly;
}

std::array< poly512, 256 > form_deg2(const poly512& mod_poly) noexcept;
poly512 mod_mult(const poly512& mod_poly, const poly512& poly1, const poly512& poly2) noexcept;

const poly512 zaitsev::lrnd32::mod_poly512_ = form_mod_poly< 512 >();
const poly256 zaitsev::lrnd32::mod_poly256_ = form_mod_poly< 256 >();
const unsigned long long zaitsev::lrnd32::mod_poly256_ull_[4] = {0x8000000000000000, 0x0, 0x0, 0x80000089};
const std::array< poly512, 256 > zaitsev::lrnd32::deg2_ = form_deg2(lrnd32::mod_poly512_);

zaitsev::lrnd32::lrnd32():
  poly_{},
  generated_number_{}
{
  this->seed(41);
}

zaitsev::lrnd32::lrnd32(size_t seed):
  poly_{},
  poly_ull_{},
  generated_number_{}
{
  this->seed(seed);
}

unsigned int zaitsev::lrnd32::max() noexcept
{
  return 0xffffffffu;
}

unsigned int zaitsev::lrnd32::min() noexcept
{
  return 0x00000000u;
}

unsigned int zaitsev::lrnd32::operator()() noexcept
{
  generated_number_ = 0;
  for (size_t i = 0; i < 32; ++i)
  {
    poly_ <<= 1;
    generated_number_ <<= 1;
    if (poly_[255])
    {
      poly_ ^= mod_poly256_;
      generated_number_ |= 1;
    }
  }
  return generated_number_;
}

unsigned int zaitsev::lrnd32::operator()(bool) noexcept
{
  generated_number_ = 0;
  for (size_t i = 0; i < 32; ++i)
  {
    poly_ull_[0] <<= 1;
    poly_ull_[0] |= bool(poly_ull_[1] & 0x8000000000000000);

    poly_ull_[1] <<= 1;
    poly_ull_[1] |= bool(poly_ull_[2] & 0x8000000000000000);

    poly_ull_[2] <<= 1;
    poly_ull_[2] |= bool(poly_ull_[3] & 0x8000000000000000);

    poly_ull_[3] <<= 1;

    generated_number_ <<= 1;
    if (poly_ull_[0] & 0x8000000000000000)
    {
      poly_ull_[0] ^= mod_poly256_ull_[0];
      poly_ull_[3] ^= mod_poly256_ull_[3];
      generated_number_ |= 1;
    }
  }
  return generated_number_;
}

void zaitsev::lrnd32::seed(size_t seed)
{
  poly512 poly{};
  poly[0] = 1;
  size_t offset = basic_offset_;
  for (size_t i = 0; offset; ++i, offset >>= 1)
  {
    if (offset & 1)
    {
      poly = mod_mult(mod_poly512_, poly, deg2_[i]);
    }
  }

  for (size_t i = 32; seed; ++i)
  {
    if (seed & 1)
    {
      poly = mod_mult(mod_poly512_, poly, deg2_[i]);
    }
    seed >>= 1;
  }
  this->poly_ = poly256(poly.to_string().substr(256, 256));

  for (size_t i = 0; i < 4; ++i)
  {
    unsigned long long temp = 1;
    for (size_t j = 0; j < 64; ++j)
    {
      if (this->poly_[i * 64 + j])
      {
        poly_ull_[3 - i] |= temp;
      }
      temp <<= 1;
    }
  }
  return;
}

void zaitsev::lrnd32::discard(size_t z)
{
  poly512 poly(this->poly_.to_string());
  for (size_t i = 0; z; ++i)
  {
    if (z & 1)
    {
      poly = mod_mult(mod_poly512_, poly, deg2_[5 + i]);
    }
    z >>= 1;
  }
  this->poly_ = poly256(poly.to_string().substr(256, 256));

  return;
}

poly512 mod_mult(const poly512& mod_poly, const poly512& poly1, const poly512& poly2) noexcept
{
  poly512 res_poly{};
  for (size_t i = 0; i < 256; ++i)
  {
    if (poly1[i])
    {
      res_poly ^= poly2 << i;
    }
  }
  for (size_t i = 511; i > 255; --i)
  {
    if (res_poly[i])
    {
      res_poly ^= mod_poly << (i - 255);
    }
  }
  return res_poly;
}

std::array< poly512, 256 > form_deg2(const poly512& mod_poly) noexcept
{
  std::array< poly512, 256 > deg2{};

  deg2[0][1] = 1;
  for (size_t i = 1; i < 256; ++i)
  {
    deg2[i] = mod_mult(mod_poly, deg2[i - 1], deg2[i - 1]);
  }
  return deg2;
}
