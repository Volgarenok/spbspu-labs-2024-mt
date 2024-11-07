#include "lrnd32.hpp"
#include <bitset>
#include <array>

poly510 form_mod_poly();
std::array< poly510, 256 > form_deg2(const poly510& mod_poly);
poly510 mod_mult(const poly510& mod_poly, const poly510& poly1, const poly510& poly2);

const poly510 lrnd32::mod_poly = form_mod_poly();
const std::array< poly510, 256 > lrnd32::deg2 = form_deg2(lrnd32::mod_poly);

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
      poly ^= mod_poly;
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
  poly.reset();
  poly[0] = 1;
  for (size_t i = 0; basic_offset_; ++i)
  {
    if (basic_offset_ & 1)
    {
      poly = mod_mult(mod_poly, poly, deg2[i]);
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
      poly = mod_mult(mod_poly, poly, deg2[i]);
    }
    seed >>= 1;
  }
  return;
}

poly510 mod_mult(const poly510& mod_poly, const poly510& poly1, const poly510& poly2)
{
  poly510 res_poly{}, temp_poly{};
  for (size_t i = 0; i < 256; ++i)
  {
    if (poly1[i])
    {
      temp_poly = poly2 << i;
      res_poly ^= temp_poly;
    }
  }
  for (size_t i = 509; i > 255; --i)
  {
    if (res_poly[i])
    {
      temp_poly = mod_poly << (i - 255);
      res_poly ^= temp_poly;
    }
  }
  return res_poly;
}

poly510 form_mod_poly()
{
  poly510 mod_poly{};
  mod_poly[0] = 1;
  mod_poly[3] = 1;
  mod_poly[7] = 1;
  mod_poly[31] = 1;
  mod_poly[255] = 1;
  return mod_poly;
}

std::array< poly510, 256 > form_deg2(const poly510& mod_poly)
{
  std::array< poly510, 256 > deg2{};

  deg2[0][1] = 1;
  for (size_t i = 1; i < 256; ++i)
  {
    deg2[i] = mod_mult(mod_poly, deg2[i - 1], deg2[i - 1]);
  }
  return deg2;
}
