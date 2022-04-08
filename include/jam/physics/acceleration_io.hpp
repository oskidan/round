#pragma once
#include "jam/physics/acceleration.hpp"
#include <iosfwd>

namespace jam {
std::ostream &operator<<(std::ostream &, struct acceleration);
}