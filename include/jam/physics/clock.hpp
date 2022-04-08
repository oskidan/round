#pragma once
#include <chrono>
#include <utility>

#include "jam/physics/time.hpp"

namespace jam {

struct [[nodiscard]] clock final
{
  jam::time update()
  {
    auto const last_tick = std::exchange(tick_, std::chrono::high_resolution_clock::now());
    auto const duration_since_last_tick = std::chrono::duration<float>(tick_ - last_tick);
    return jam::time{ duration_since_last_tick.count() };
  }

private:
  std::chrono::high_resolution_clock::time_point tick_ = std::chrono::high_resolution_clock::now();
};

}// namespace jam