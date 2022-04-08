#include "jam/math/scalar_io.hpp"
#include "jam/math/vector.hpp"

#include <iostream>

namespace jam {

std::ostream &operator<<(std::ostream &lhs, vector const rhs)
{
  return lhs << "vector(" << rhs.x() << ", " << rhs.y() << ")";
}

}// namespace jam