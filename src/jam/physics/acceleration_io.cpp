#include "jam/math/vector_io.hpp"
#include "jam/physics/acceleration.hpp"

#include <iostream>

namespace jam {

std::ostream &operator<<(std::ostream &lhs, acceleration const rhs)
{
  return lhs << static_cast<vector>(rhs) << "m/s²";
}

}// namespace jam