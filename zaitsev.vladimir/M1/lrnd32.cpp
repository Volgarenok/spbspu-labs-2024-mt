#include "lrnd32.hpp"
#include <bitset>
#include <array>

template < size_t N >
std::bitset< N > form_mod_poly()
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

std::array< poly512, 256 > form_deg2(const poly512& mod_poly);
poly512 mod_mult(const poly512& mod_poly, const poly512& poly1, const poly512& poly2);

const poly512 lrnd32::mod_poly512 = form_mod_poly< 512 >();
const poly256 lrnd32::mod_poly256 = form_mod_poly< 256 >();
const std::array< poly512, 256 > lrnd32::deg2 = form_deg2(lrnd32::mod_poly512);

lrnd32::lrnd32(size_t seed):
  poly{},
  basic_offset_{ 183758644 },
  generated_number_{}
{
  set_start_value(seed);
}

unsigned int lrnd32::generate_next()
{
  generated_number_ = 0;
  for (size_t i = 0; i < 32; ++i)
  {
    poly <<= 1;
    if (poly[255])
    {
      poly ^= mod_poly256;
    }
    generated_number_ <<= 1;
    if (poly[0])
    {
      generated_number_ |= 1;
    }
  }
  return generated_number_;
}

void lrnd32::set_start_value(size_t seed)
{
  poly512 poly{};
  poly[0] = 1;
  for (size_t i = 0; basic_offset_; ++i)
  {
    if (basic_offset_ & 1)
    {
      poly = mod_mult(mod_poly512, poly, deg2[i]);
    }
    basic_offset_ >>= 1;
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
  return;
}

poly512 mod_mult(const poly512& mod_poly, const poly512& poly1, const poly512& poly2)
{
  poly512 res_poly{}, temp_poly{};
  for (size_t i = 0; i < 256; ++i)
  {
    if (poly1[i])
    {
      temp_poly = poly2 << i;
      res_poly ^= temp_poly;
    }
  }
  for (size_t i = 511; i > 255; --i)
  {
    if (res_poly[i])
    {
      temp_poly = mod_poly << (i - 255);
      res_poly ^= temp_poly;
    }
  }
  return res_poly;
}

std::array< poly512, 256 > form_deg2(const poly512& mod_poly)
{
  std::array< poly512, 256 > deg2{};

  deg2[0][1] = 1;
  for (size_t i = 1; i < 256; ++i)
  {
    deg2[i] = mod_mult(mod_poly, deg2[i - 1], deg2[i - 1]);
  }
  return deg2;
}
