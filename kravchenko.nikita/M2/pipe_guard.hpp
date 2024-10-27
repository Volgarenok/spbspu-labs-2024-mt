#ifndef PIPE_GUARD_HPP
#define PIPE_GUARD_HPP

#include <unistd.h>

namespace kravchenko
{
  template < bool isToWrite >
  class PipeGuard
  {
  public:
    PipeGuard(int fds[2]);
    ~PipeGuard();

  private:
    int fdsOnClose_;
  };
}

template < bool isToWrite >
kravchenko::PipeGuard< isToWrite >::PipeGuard(int fds[2]):
  fdsOnClose_(fds[isToWrite])
{
  close(fds[!isToWrite]);
  fds[!isToWrite] = -1;
}

template < bool isToWrite >
kravchenko::PipeGuard< isToWrite >::~PipeGuard()
{
  close(fdsOnClose_);
}

#endif