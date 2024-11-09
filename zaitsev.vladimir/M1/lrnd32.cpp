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

const size_t lrnd32::basic_offset_ = 183758644ull;
const poly512 lrnd32::mod_poly512 = form_mod_poly< 512 >();
const poly256 lrnd32::mod_poly256 = form_mod_poly< 256 >();
const std::array< poly512, 256 > lrnd32::deg2 = form_deg2(lrnd32::mod_poly512);

lrnd32::lrnd32():
  poly{},
  generated_number_{}
{
  this->seed(41);
}

lrnd32::lrnd32(result_type seed):
  poly{},
  generated_number_{}
{
  this->seed(seed);
}

unsigned int lrnd32::max()
{
  return 0xffffffffu;
}

unsigned int lrnd32::min()
{
  return 0x00000000u;
}

unsigned int lrnd32::operator()()
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

void lrnd32::seed(result_type seed)
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
