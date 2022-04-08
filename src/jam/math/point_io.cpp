#include "jam/math/point.hpp"
#include "jam/math/scalar_io.hpp"

#include <iostream>

namespace jam {
std::ostream &operator<<(std::ostream &lhs, point const rhs)
{
  return lhs << "point(" << rhs.x() << ", " << rhs.y() << ")";
}
}// namespace jam