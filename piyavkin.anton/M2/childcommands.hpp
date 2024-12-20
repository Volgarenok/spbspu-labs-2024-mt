#ifndef CHILDCOMMANDS_HPP
#define CHILDCOMMANDS_HPP
#include <random>
#include <map>
#include <thread>

namespace piyavkin
{
  using calc_t = std::map< std::string, double >;
  void calculateAreaSet(calc_t& calc, std::minstd_rand& gen, const std::string& str, std::map< std::string, std::thread >& ths);
  void sendStatus(calc_t& calc, const std::string& str, int sock, std::map< std::string, std::thread >& ths);
  void waitStatus(calc_t& calc, const std::string& str, int sock, std::map< std::string, std::thread >& ths);
}
#endif