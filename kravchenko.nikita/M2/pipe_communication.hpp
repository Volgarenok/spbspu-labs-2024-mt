#ifndef PIPE_COMMUNICATION_HPP
#define PIPE_COMMUNICATION_HPP

#include <cstring>
#include <exception>
#include <unistd.h>
#include "circle.hpp"
#include "commands.hpp"

namespace kravchenko
{
  template < class T >
  void pipePush(int fdsWrite, const T& obj);

  template < class T >
  void pipePop(int fdsRead, T& obj);
}

template < class T >
void kravchenko::pipePush(int fdsWrite, const T& obj)
{
  int ret = write(fdsWrite, &obj, sizeof(obj));
  if (ret < 0)
  {
    throw std::runtime_error(strerror(errno));
  }
  else if (static_cast< size_t >(ret) < sizeof(obj))
  {
    throw std::runtime_error("Non-consistent writing");
  }
}

template < class T >
void kravchenko::pipePop(int fdsRead, T& obj)
{
  T temp;
  int ret = read(fdsRead, &temp, sizeof(temp));
  while (ret == 0)
  {
    ret = read(fdsRead, &temp, sizeof(temp));
  }
  obj = std::move(temp);
  if (ret < 0)
  {
    throw std::runtime_error(strerror(errno));
  }
  else if (static_cast< size_t >(ret) < sizeof(obj))
  {
    throw std::runtime_error("Non-consistent reading");
  }
}

#endif