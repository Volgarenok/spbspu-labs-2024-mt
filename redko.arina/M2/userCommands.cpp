#include "userCommands.hpp"
#include <iostream>
#include <functional>
#include <iterator>

void redko::createCircle(std::istream & in, map_t &, set_t & circleSet, std::map< std::string, Calculation > &, std::ostream &)
{
  std::string name = "";
  int radius, x, y;
  in >> name >> radius >> x >> y;
  if (!in || radius <= 0)
  {
    throw std::logic_error("wrong input parameters");
  }
  if (circleSet.count(name) == 1)
  {
    throw std::logic_error("circle with name " + name + " already exists");
  }
  circleSet.insert({ name, radius, { static_cast< double >(x), static_cast< double >(y) } });
}

void redko::createSet(std::istream & in, map_t & setMap, set_t & circleSet, std::map< std::string, Calculation > &, std::ostream &)
{
  std::string name = "";
  size_t size = 0;
  in >> name >> size;
  if (!in || size < 1)
  {
    throw std::logic_error("wrong input parameters");
  }
  if (setMap.count(name) == 1)
  {
    throw std::logic_error("set with name " + name + " already exists");
  }
  set_it newSet = (setMap.emplace(name, std::set< Circle >())).first;
  circle_it circle;
  std::string circleName = "";
  for (size_t i = 0; i < size; ++i)
  {
    in >> circleName;
    circle = circleSet.find(circleName);
    if (circle == circleSet.end())
    {
      setMap.erase(newSet);
      throw std::logic_error("cannot find circle with name " + circleName);
    }
    newSet->second.insert(*circle);
  }
}

void redko::showCircle(std::istream & in, map_t &, set_t & circleSet, std::map< std::string, Calculation > &, std::ostream & out)
{
  std::string name = "";
  in >> name;
  circle_it circleIt = circleSet.find(name);
  if (circleIt == circleSet.end())
  {
    throw std::logic_error("cannot find circle with name " + name);
  }
  out << *circleIt << "\n";
}

void redko::showSet(std::istream & in, map_t & setMap, set_t &, std::map< std::string, Calculation > &, std::ostream & out)
{
  std::string name = "";
  in >> name;
  set_it setIt = setMap.find(name);
  if (setIt == setMap.end())
  {
    throw std::logic_error("cannot find set with name " + name);
  }
  using namespace std::placeholders;
  std::copy(setIt->second.begin(), setIt->second.end(), std::ostream_iterator< Circle >(out, "\n"));
}

void redko::showCircleFrame(std::istream & in, map_t &, set_t & circleSet, std::map< std::string, Calculation > &, std::ostream & out)
{
  std::string name = "";
  in >> name;
  circle_it circleIt = circleSet.find(name);
  if (circleIt == circleSet.end())
  {
    throw std::logic_error("cannot find circle with name " + name);
  }
  Point left = { circleIt->center.x - circleIt->radius, circleIt->center.y - circleIt->radius };
  Point right = { circleIt->center.x + circleIt->radius, circleIt->center.y + circleIt->radius };
  out << left << ' ' << right << '\n';
}

void redko::showSetFrame(std::istream & in, map_t & setMap, set_t &, std::map< std::string, Calculation > &, std::ostream & out)
{
  std::string name = "";
  in >> name;
  set_it setIt = setMap.find(name);
  if (setIt == setMap.end())
  {
    throw std::logic_error("cannot find set with name " + name);
  }
  std::pair<Point, Point> frame = getSetFrame(setIt);
  out << frame.first << ' ' << frame.second << '\n';
}

void redko::calculateSetArea(std::istream & in, map_t & setMap, set_t &, std::map< std::string, Calculation > & calcs, std::ostream &)
{
  std::string calcName = "";
  std::string setName = "";
  int threads = 0;
  long long tries = 0;
  in >> calcName >> setName >> threads >> tries;
  if (!in || threads < 1 || tries < 1)
  {
    throw std::logic_error("invalid parameters");
  }
  set_it setIt = setMap.find(setName);
  if (setIt == setMap.end())
  {
    throw std::logic_error("cannot find set with name " + setName);
  }
  std::map< std::string, Calculation >::iterator calcIt = calcs.find(calcName);
  if (calcIt != calcs.end())
  {
    throw std::logic_error("calc with name " + calcName + " already exists");
  }
  calcs[calcName] = Calculation();
  calcs[calcName].start(setIt, threads, tries, 0);
}

void redko::showStatus(std::istream & in, map_t &, set_t &, std::map< std::string, Calculation > & calcs, std::ostream & out)
{
  std::string calcName = "";
  in >> calcName;
  std::map< std::string, Calculation >::iterator calcIt = calcs.find(calcName);
  if (calcIt == calcs.end())
  {
    throw std::logic_error("cannot find calc with name " + calcName);
  }
  if (calcIt->second.isCalculated())
  {
    out << calcIt->second.getResult() << '\n';
  }
  else
  {
    out << "<IN PROGRESS>\n";
  }
}

void redko::wait(std::istream & in, map_t &, set_t &, std::map< std::string, Calculation > & calcs, std::ostream & out)
{
  std::string calcName = "";
  in >> calcName;
  std::map< std::string, Calculation >::iterator calcIt = calcs.find(calcName);
  if (calcIt == calcs.end())
  {
    throw std::logic_error("cannot find calc with name " + calcName);
  }
  if (!calcIt->second.isCalculated())
  {
    calcIt->second.wait();
  }
  out << calcIt->second.getResult() << '\n';
}
