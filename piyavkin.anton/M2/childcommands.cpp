#include "childcommands.hpp"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <thread>
#include "getsquare.hpp"
#include "createpoints.hpp"
#include "set.hpp"

void getMonteCarlo(piyavkin::calc_t& calc, std::minstd_rand& gen, piyavkin::data_t& points, const piyavkin::rectangle_t& r, size_t tries, const piyavkin::Set& st, size_t th, const std::string& name)
{
  createPoints(gen, points, r, tries);
  double square = getSquare(points, st, r, th);
  calc[name] = square;
}

void piyavkin::calculateAreaSet(calc_t& calc, std::minstd_rand& gen, const std::string& tn, std::map< std::string, std::thread >& ths)
{
  size_t curr = tn.find(' ');
  std::string name(tn.substr(0, curr));
  ++curr;
  size_t temp = tn.find(' ', curr);
  size_t th = std::stoull(tn.substr(curr, tn.find(' ', curr)));
  curr = temp + 1;
  size_t tries = std::stoull(tn.substr(curr, tn.find(' ', curr)));
  Set st = parse(tn.substr(tn.find(' ', curr) + 1));
  data_t points;
  rectangle_t r = st.getFrame();
  ths[name] = std::thread(getMonteCarlo, std::ref(calc), std::ref(gen), std::ref(points), std::cref(r), tries, std::cref(st), th, std::cref(name));
}

void piyavkin::sendStatus(calc_t& calc, const std::string& str, int sock, std::map< std::string, std::thread >& ths)
{
  std::cout << str << ' ';
  auto it = calc.find(str);
  if (it == calc.end())
  {
    const char* msg = "<IN PROGRESS>";
    send(sock, msg, std::strlen(msg), 0);
  }
  else
  {
    double square = calc.find(str)->second;
    std::string squareStr(std::to_string(square));
    std::cout << square << '\n';
    ths[str].join();
    ths.erase(str);
    send(sock, squareStr.c_str(), squareStr.size(), 0);
  }
}

void piyavkin::waitStatus(calc_t& calc, const std::string& str, int sock, std::map< std::string, std::thread >& ths)
{
  ths[str].join();
  ths.erase(str);
  std::string squareStr(std::to_string(calc.find(str)->second));
  send(sock, squareStr.c_str(), squareStr.size(), 0);
}