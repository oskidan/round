#include "jam/math/scalar.hpp"

#include <iostream>

namespace jam {

std::ostream &operator<<(std::ostream &lhs, scalar const rhs) { return lhs << static_cast<float>(rhs); }

}// namespace jam