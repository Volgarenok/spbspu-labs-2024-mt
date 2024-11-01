#ifndef PIPE_CHANNEL_HPP
#define PIPE_CHANNEL_HPP

#include <cstring>
#include <stdexcept>
#include <unistd.h>

namespace kravchenko
{
  class PipeChannel
  {
  public:
    PipeChannel(int fdsPipeRead[2], int fdsPipeWrite[2]);
    PipeChannel(const PipeChannel&) = delete;
    PipeChannel(PipeChannel&&) = delete;
    PipeChannel& operator=(const PipeChannel&) = delete;
    PipeChannel& operator=(PipeChannel&&) = delete;
    ~PipeChannel();

    template < class T >
    void push(const T& obj);

    template < class T >
    void pop(T& obj);

  private:
    int fdsToRead_;
    int fdsToWrite_;
  };
}

template < class T >
void kravchenko::PipeChannel::push(const T& obj)
{
  const char* objPtr = reinterpret_cast< const char* >(std::addressof(obj));
  size_t objSize = sizeof(obj);
  for (size_t bytes = 0; bytes < objSize;)
  {
    int ret = write(fdsToWrite_, objPtr + bytes, objSize - bytes);
    if (ret < 0)
    {
      throw std::runtime_error(strerror(errno));
    }
    bytes += ret;
  }
}

template < class T >
void kravchenko::PipeChannel::pop(T& obj)
{
  char* objPtr = reinterpret_cast< char* >(std::addressof(obj));
  size_t objSize = sizeof(obj);
  for (size_t bytes = 0; bytes < objSize;)
  {
    int ret = read(fdsToRead_, objPtr + bytes, objSize - bytes);
    if (ret < 0)
    {
      throw std::runtime_error(strerror(errno));
    }
    bytes += ret;
  }
}

#endif