#include "CircleOutput.hpp"
#include <ostream>
#include <iomanip>
#include "FormatGuard.hpp"

std::ostream& novikov::operator<<(std::ostream& out, const CircleOutput& circle)
{
  std::ostream::sentry sentry(out);

  if (!out)
  {
    return out;
  }

  FormatGuard guard(out);
  out << std::fixed << std::setprecision(3) << circle.elapsed_time << " " << circle.area << "\n";
  return out;
}
