#ifndef UNLINKFILEGUARD_HPP
#define UNLINKFILEGUARD_HPP

namespace piyavkin
{
  class UnlinkFileGuard
  {
  public:
    UnlinkFileGuard(int des, char* name);
    ~UnlinkFileGuard();
  private:
    int des_;
    char* name_;
  };
}
#endif