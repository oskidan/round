#include "jam/physics/mass.hpp"

#include <iostream>

namespace jam {

std::ostream &operator<<(std::ostream &lhs, mass const mass) { return lhs << static_cast<float>(mass) << "kg"; }

}// namespace jam