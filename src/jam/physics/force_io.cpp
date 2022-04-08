#include "jam/math/vector_io.hpp"
#include "jam/physics/force.hpp"

#include <iostream>

namespace jam {

std::ostream &operator<<(std::ostream &lhs, force const rhs) { return lhs << static_cast<vector>(rhs) << "kg·m/s²"; }

}// namespace jam