#include "lrnd32.hpp"
#include <bitset>
#include <array>

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

const poly512 lrnd32::mod_poly512 = form_mod_poly< 512 >();
const poly256 lrnd32::mod_poly256 = form_mod_poly< 256 >();
const unsigned long long lrnd32::mod_poly256_ull[4] = {0x8000000000000000, 0x0, 0x0, 0x80000089};
const std::array< poly512, 256 > lrnd32::deg2 = form_deg2(lrnd32::mod_poly512);

lrnd32::lrnd32():
  poly{},
  generated_number_{}
{
  this->seed(41);
}

lrnd32::lrnd32(size_t seed):
  poly{},
  poly_ull{},
  generated_number_{}
{
  this->seed(seed);
}

unsigned int lrnd32::max() noexcept
{
  return 0xffffffffu;
}

unsigned int lrnd32::min() noexcept
{
  return 0x00000000u;
}

unsigned int lrnd32::operator()() noexcept
{
  generated_number_ = 0;
  for (size_t i = 0; i < 32; ++i)
  {
    poly <<= 1;
    generated_number_ <<= 1;
    if (poly[255])
    {
      poly ^= mod_poly256;
      generated_number_ |= 1;
    }
  }
  return generated_number_;
}

unsigned int lrnd32::operator()(bool) noexcept
{
  generated_number_ = 0;
  for (size_t i = 0; i < 32; ++i)
  {
    poly_ull[0] <<= 1;
    poly_ull[0] |= bool(poly_ull[1] & 0x8000000000000000);

    poly_ull[1] <<= 1;
    poly_ull[1] |= bool(poly_ull[2] & 0x8000000000000000);

    poly_ull[2] <<= 1;
    poly_ull[2] |= bool(poly_ull[3] & 0x8000000000000000);

    poly_ull[3] <<= 1;

    generated_number_ <<= 1;
    if (poly_ull[0] & 0x8000000000000000)
    {
      poly_ull[0] ^= mod_poly256_ull[0];
      poly_ull[3] ^= mod_poly256_ull[3];
      generated_number_ |= 1;
    }
  }
  return generated_number_;
}

void lrnd32::seed(size_t seed)
{
  poly512 poly{};
  poly[0] = 1;
  size_t offset = basic_offset_;
  for (size_t i = 0; offset; ++i, offset >>= 1)
  {
    if (offset & 1)
    {
      poly = mod_mult(mod_poly512, poly, deg2[i]);
    }
  }

  if (!seed)
  {
    return;
  }

  for (size_t i = 32; seed; ++i)
  {
    if (seed & 1)
    {
      poly = mod_mult(mod_poly512, poly, deg2[i]);
    }
    seed >>= 1;
  }
  this->poly = poly256(poly.to_string().substr(256, 256));

  for (size_t i = 0; i < 4; ++i)
  {
    unsigned long long temp = 1;
    for (size_t j = 0; j < 64; ++j)
    {
      if (this->poly[i * 64 + j])
      {
        poly_ull[3 - i] |= temp;
      }
      temp <<= 1;
    }
  }
  return;
}

void lrnd32::discard(size_t z)
{
  poly512 poly(this->poly.to_string());
  for (size_t i = 0; z; ++i)
  {
    if (z & 1)
    {
      poly = mod_mult(mod_poly512, poly, deg2[5 + i]);
    }
    z >>= 1;
  }
  this->poly = poly256(poly.to_string().substr(256, 256));

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
