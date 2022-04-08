
#include "jam/math/vector_io.hpp"
#include "jam/physics/velocity.hpp"

#include <iostream>

namespace jam {
std::ostream &operator<<(std::ostream &lhs, velocity const rhs) { return lhs << static_cast<vector>(rhs) << "m/s"; }

}// namespace jam