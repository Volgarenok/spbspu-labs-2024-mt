#include "commands.hpp"
#include <stdexcept>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>

void piyavkin::inputOb(std::istream& in, const std::string& name, circle_t& mp)
{
  Circle res;
  in >> res;
  if (!in)
  {
    throw std::logic_error("The circle is not created");
  }
  mp[name] = res;
}

void piyavkin::inputOb(std::istream& in, const std::string& nameSet, set_t& sets, const circle_t& c)
{
  long long n = 0;
  in >> n;
  if (!in)
  {
    throw std::logic_error("The set is not created");
  }
  if (n <= 0)
  {
    throw std::logic_error("The set is not created");
  }
  const size_t size = n;
  Set res;
  for (size_t i = 0; i < size; ++i)
  {
    std::string name;
    in >> name;
    if (c.find(name) != c.end())
    {
      res.insert(c.at(name));
    }
    else
    {
      throw std::logic_error("The set is not created");
    }
  }
  sets[nameSet] = res;
}

void piyavkin::calcArea(std::istream& in, set_t& sets, calc_t& calcs, int socket)
{
  std::string calcName;
  std::string setName;
  long long th = 0;
  long long tries = 0;
  in >> calcName >> setName >> th >> tries;
  auto it = sets.find(setName);
  if (!in || tries <= 0 || th <= 0 || it == sets.end())
  {
    throw std::logic_error("Incorrect parameters for area command");
  }
  std::string str;
  str += std::to_string(th) + ' ' + std::to_string(tries) + ' ' + it->second.getStr();
  const char* cstr = str.c_str();
  int bytesSent = send(socket, cstr, strlen(cstr), MSG_NOSIGNAL);
  if (bytesSent < 0)
  {
    throw std::logic_error("Error sending data");
  }
  calcs[calcName] = 0;
}