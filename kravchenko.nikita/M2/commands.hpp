#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "circle.hpp"
#include "pipe_channel.hpp"
#include "queries.hpp"

namespace kravchenko
{
  using CircleMap = std::unordered_map< std::string, Circle >;
  using CircleWrappedData = std::vector< std::reference_wrapper< const Circle > >;
  using CircleSetMap = std::unordered_map< std::string, CircleWrappedData >;

  using CalcMap = std::unordered_map< std::string, double >;

  void cmdCircle(CircleMap& circles, std::istream& in, std::ostream&);
  void cmdSet(CircleSetMap& sets, const CircleMap& circles, std::istream& in, std::ostream&);
  void cmdShow(const CircleMap& circles, std::istream& in, std::ostream& out);
  void cmdShowSet(const CircleSetMap& sets, std::istream& in, std::ostream& out);
  void cmdFrame(const CircleMap& circles, std::istream& in, std::ostream& out);
  void cmdFrameSet(const CircleSetMap& sets, std::istream& in, std::ostream& out);

  void cmdArea(PipeChannel& channel, const CircleSetMap& sets, CalcMap& calcs, std::istream& in, std::ostream&);
  template < bool isWait >
  void cmdSync(PipeChannel& channel, CalcMap& calcs, std::istream& in, std::ostream& out);

  namespace cmd
  {
    template < class Map >
    typename Map::const_iterator findElement(const Map& map, std::istream& in);

    template < class CircleDataConstIt >
    Frame getFrameSet(CircleDataConstIt cbegin, CircleDataConstIt cend);

    struct FramePred
    {
      FramePred(const Circle& c);
      void operator()(const Circle& c);
      Frame frame;
    };

    void printArea(std::ostream& out, double area);
  }
}

template < class Map >
typename Map::const_iterator kravchenko::cmd::findElement(const Map& map, std::istream& in)
{
  std::string name;
  if (!(in >> name))
  {
    throw std::invalid_argument("<INVALID INPUT>");
  }
  typename Map::const_iterator foundIt = map.find(name);
  if (foundIt == map.cend())
  {
    throw std::invalid_argument("<ELEMENT " + name + " NOT FOUND>");
  }
  return foundIt;
}

template < class CircleDataConstIt >
kravchenko::Frame kravchenko::cmd::getFrameSet(CircleDataConstIt cbegin, CircleDataConstIt cend)
{
  FramePred pred(*(cbegin++));
  std::for_each(cbegin, cend, std::ref(pred));
  return pred.frame;
}

template < bool isWait >
void kravchenko::cmdSync(PipeChannel& channel, CalcMap& calcs, std::istream& in, std::ostream& out)
{
  auto statusIt = cmd::findElement(calcs, in);
  if ((*statusIt).second != 0.0)
  {
    cmd::printArea(out, (*statusIt).second);
    return;
  }

  channel.push((isWait) ? QueryType::WAIT : QueryType::STATUS);
  channel.pushContainer((*statusIt).first);

  bool isReady = false;
  channel.pop(isReady);
  if (isReady)
  {
    double area = 0.0;
    channel.pop(area);
    calcs[(*statusIt).first] = area;
    cmd::printArea(out, area);
  }
  else if (!isWait)
  {
    out << "<IN PROGRESS>\n";
  }
}

#endif