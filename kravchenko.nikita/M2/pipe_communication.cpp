#include "pipe_communication.hpp"

template <>
void kravchenko::pipePush< std::string >(int fdsWrite, const std::string& msg)
{
  pipePush(fdsWrite, msg.size());
  for (char c : msg)
  {
    pipePush(fdsWrite, c);
  }
}

template <>
void kravchenko::pipePop< std::string >(int fdsRead, std::string& msg)
{
  size_t size = 0;
  pipePop(fdsRead, size);
  std::string temp(size, 0);
  for (size_t i = 0; i < size; ++i)
  {
    char c = 0;
    pipePop(fdsRead, c);
    temp[i] = c;
  }
  msg = std::move(temp);
}