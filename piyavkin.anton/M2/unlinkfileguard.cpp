#include "unlinkfileguard.hpp"
#include <fcntl.h>
#include <unistd.h>

piyavkin::UnlinkFileGuard::UnlinkFileGuard(int des, const char* name):
  des_(des),
  name_(name)
{}

piyavkin::UnlinkFileGuard::~UnlinkFileGuard()
{
  close(des_);
  unlink(name_);
}