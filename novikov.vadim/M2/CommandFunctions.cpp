#include "CommandFunctions.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <cstddef>
#include <SizeType.hpp>
#include "Circle.hpp"

void novikov::cmd::circle(std::istream& in, std::ostream& out, circle_collection_t& circles)
{
  std::string name;
  SizeType r;
  Point c;

  in >> name >> r >> c;

  if (!in)
  {
    throw std::invalid_argument("Ошибка ввода!");
  }

  if (name.empty() || !std::isalpha(name[0]))
  {
    throw std::invalid_argument("Некорректное имя круга!");
  }

  if (circles.find(name) != circles.cend())
  {
    throw std::invalid_argument("Такой круг уже существует!");
  }

  circles[name] = {r.size, c};
  out << "Создана новая фигура " << name << "\n";
}

void novikov::cmd::set(std::istream& in, std::ostream& out, circle_set_collection_t& circle_sets)
{
  std::string name;
  SizeType set_size;
  
  in >> name >> set_size;
 
  std::vector< std::string > circles(set_size.size);
  using input_it_t = std::istream_iterator< std::string >;
  std::copy_n(input_it_t(std::cin), set_size.size, circles.begin());

  if (!in)
  {
    throw std::invalid_argument("Ошибка ввода!");
  }

  if (circle_sets.find(name) != circle_sets.cend())
  {
    throw std::invalid_argument("Такой набор уже существует!");
  }

  circle_sets[name] = std::move(circles);
  out << "Создан набор кругов " << name << "\n";
}

void novikov::cmd::show(std::istream& in, std::ostream& out, const circle_collection_t& circles)
{
  std::string circle_name;
  in >> circle_name;

  if (!in)
  {
    throw std::invalid_argument("Ошибка ввода!");
  }

  try
  {
    out << circles.at(circle_name) << "\n";
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument("Круга " + circle_name + " не существует!");
  }
}

void novikov::cmd::showset(std::istream& in, std::ostream& out, const circle_collection_t& circles, const circle_set_collection_t& circle_sets)
{
  std::string set_name;
  in >> set_name;

  if (!in)
  {
    throw std::invalid_argument("Ошибка ввода!");
  }

  auto circle_set = circle_sets.at(set_name);
  std::transform(circle_set.cbegin(), circle_set.cend(), std::ostream_iterator< Circle >(out, "\n"), [&circles](const std::string& name)
  {
    return circles.at(name);
  });
}

void novikov::cmd::frame(std::istream& in, std::ostream& out, const circle_collection_t& circles)
{
  std::string circle_name;
  in >> circle_name;

  if (!in)
  {
    throw std::invalid_argument("Ошибка ввода!");
  }

  try
  {
    out << getFrame(circles.at(circle_name)) << "\n";
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument("Круга " + circle_name + " не существует!");
  }
}
