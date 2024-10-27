#include "pipe_communication.hpp"
#include "commands.hpp"

template <>
void kravchenko::pipePush< kravchenko::CircleData >(int fdsWrite, const CircleData& data)
{
  pipePush(fdsWrite, data.size());
  for (const Circle& c : data)
  {
    pipePush(fdsWrite, c);
  }
}

template <>
void kravchenko::pipePop< kravchenko::CircleData >(int fdsRead, CircleData& data)
{
  size_t size = 0;
  pipePop(fdsRead, size);
  CircleData temp(size);
  for (size_t i = 0; i < size; ++i)
  {
    Circle c;
    pipePop(fdsRead, c);
    temp[i] = std::move(c);
  }
  data = std::move(temp);
}