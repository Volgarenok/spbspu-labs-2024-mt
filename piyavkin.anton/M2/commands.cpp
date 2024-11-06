#include "commands.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

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
  str += "a " + calcName + ' ' + std::to_string(th) + ' ' + std::to_string(tries) + ' ' + it->second.getStr();
  const char* cstr = str.c_str();
  int bytesSent = write(socket, cstr, strlen(cstr));
  if (bytesSent < 0)
  {
    throw std::logic_error("Error sending data");
  }
  calcs[calcName] = 0;
}

void piyavkin::recStatus(std::istream& in, std::ostream& out, calc_t& calcs, int socket)
{
  std::string name = "";
  in >> name;
  auto it = calcs.find(name);
  if (it == calcs.end())
  {
    throw std::logic_error("Incorrect parameter");
  }
  if (it->second != 0)
  {
    out << it->second << '\n';
  }
  else
  {
    std::string msg = "s " + name;
    const char* msgc = msg.c_str();
    int sizeSend = write(socket, msgc, std::strlen(msgc));
    if (sizeSend < 0)
    {
      throw std::logic_error(strerror(errno));
    }
    char buf[1000] = {};
    int sizeMsg = read(socket, buf, 1000);
    if (sizeMsg <= 0)
    {
      throw std::logic_error("Data not received");
    }
    out << buf << '\n';
    calcs[name] = std::stod(buf);
  }
}