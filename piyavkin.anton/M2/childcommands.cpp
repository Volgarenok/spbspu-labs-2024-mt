#include "childcommands.hpp"
#include <cstring>
#include <sys/socket.h>
#include "getsquare.hpp"
#include "createpoints.hpp"

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
  ths[name] = std::thread(getMonteCarlo, std::ref(calc), std::ref(gen), std::ref(points), std::cref(r), tries, st, th, std::cref(name));
}

void piyavkin::sendStatus(calc_t& calc, const std::string& str, int sock, std::map< std::string, std::thread >& ths)
{
  std::string newStr = str.substr(0, str.find(' '));
  auto it = calc.find(newStr);
  if (it == calc.end())
  {
    const char* msg = "<IN PROGRESS>";
    int sizeSend = send(sock, msg, std::strlen(msg), 0);
    if (sizeSend < 0)
    {
      throw std::logic_error(strerror(errno));
    }
  }
  else
  {
    double square = calc.find(newStr)->second;
    std::string squareStr(std::to_string(square));
    ths[newStr].join();
    ths.erase(newStr);
    if (send(sock, squareStr.c_str(), squareStr.size(), 0) < 0)
    {
      throw std::logic_error(strerror(errno));
    }
  }
}

void piyavkin::waitStatus(calc_t& calc, const std::string& str, int sock, std::map< std::string, std::thread >& ths)
{
  ths[str].join();
  ths.erase(str);
  std::string squareStr(std::to_string(calc.find(str)->second));
  if (send(sock, squareStr.c_str(), squareStr.size(), 0) < 0)
  {
    throw std::logic_error(strerror(errno));
  }
}