#include "jam/physics/time.hpp"

#include <iostream>

namespace jam {

std::ostream &operator<<(std::ostream &lhs, time const rhs) { return lhs << static_cast<float>(rhs) << "s"; }

}// namespace jam