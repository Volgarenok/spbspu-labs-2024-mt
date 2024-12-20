#ifndef UNLINKFILEGUARD_HPP
#define UNLINKFILEGUARD_HPP

namespace piyavkin
{
  class UnlinkFileGuard
  {
  public:
    UnlinkFileGuard(int des, const char* name);
    ~UnlinkFileGuard();
  private:
    int des_;
    const char* name_;
  };
}
#endif