#include "commands.hpp"
#include <algorithm>
#include <exception>
#include <iterator>
#include <stream_guard.hpp>
#include "monte_carlo.hpp"

void kravchenko::cmdCircle(CircleMap& circles, std::istream& in, std::ostream&)
{
  std::string name;
  Circle c;
  in >> name >> c;
  if (!in)
  {
    throw std::invalid_argument("<INVALID INPUT>");
  }
  if (circles.find(name) != circles.end())
  {
    throw std::invalid_argument("<CIRCLE ALREADY EXISTS>");
  }
  circles[name] = c;
}

void kravchenko::cmdSet(CircleSetMap& sets, const CircleMap& circles, std::istream& in, std::ostream&)
{
  std::string setName;
  size_t size = 0;
  in >> setName >> size;
  if (!in)
  {
    throw std::invalid_argument("<INVALID INPUT>");
  }
  if (sets.find(setName) != sets.end())
  {
    throw std::invalid_argument("<SET ALREADY EXISTS>");
  }
  if (size < 1)
  {
    throw std::invalid_argument("<INVALID SIZE>");
  }
  CircleWrappedData data;
  data.reserve(size);
  for (size_t i = 0; i < size; ++i)
  {
    data.push_back((*cmd::findElement(circles, in)).second);
  }
  sets[setName] = data;
}

void kravchenko::cmdShow(const CircleMap& circles, std::istream& in, std::ostream& out)
{
  out << (*cmd::findElement(circles, in)).second << '\n';
}

void kravchenko::cmdShowSet(const CircleSetMap& sets, std::istream& in, std::ostream& out)
{
  const CircleWrappedData& set = (*cmd::findElement(sets, in)).second;
  std::copy(set.cbegin(), set.cend(), std::ostream_iterator< Circle >{ out, "\n" });
}

void kravchenko::cmdFrame(const CircleMap& circles, std::istream& in, std::ostream& out)
{
  out << (*cmd::findElement(circles, in)).second.getFrame() << '\n';
}

void kravchenko::cmdFrameSet(const CircleSetMap& sets, std::istream& in, std::ostream& out)
{
  const CircleWrappedData& data = (*cmd::findElement(sets, in)).second;
  out << getFrameSet(data.cbegin(), data.cend()) << '\n';
}

void kravchenko::cmdArea(PipeChannel& channel, const CircleSetMap& sets, CalcMap& calcs, std::istream& in, std::ostream&)
{
  std::string calcName;
  in >> calcName;
  if (calcs.find(calcName) != calcs.end())
  {
    throw std::invalid_argument("<CALC ALREADY EXISTS>");
  }
  auto setToSendIt = cmd::findElement(sets, in);
  size_t threads = 0;
  size_t tries = 0;
  in >> threads >> tries;
  if (!in || threads == 0 || tries == 0 || threads > tries)
  {
    throw std::invalid_argument("<INVALID THREADS AND/OR TRIES>");
  }
  channel.push(QueryType::AREA);
  channel.pushContainer(calcName);

  std::vector< Circle > sendData;
  for (const auto& c : (*setToSendIt).second)
  {
    sendData.push_back(c);
  }
  channel.pushContainer(sendData);

  channel.push(threads);
  channel.push(tries);
  calcs[calcName] = 0.0;
}

void kravchenko::cmd::printArea(std::ostream& out, double area)
{
  if (area == -1.0)
  {
    out << "<CALC ERROR OCCURED>\n";
    return;
  }
  StreamGuard guard(out);
  out << std::setprecision(3) << std::fixed;
  out << area << '\n';
}
