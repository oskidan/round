#pragma once
#include "jam/math/scalar.hpp"

namespace jam {

// I represent reading of a clock, measured in seconds.
struct [[nodiscard]] time final
{
  // Precision of 1 millisecond.
  constexpr static inline auto epsilon = 0.001F;

  constexpr explicit time(float const value) noexcept : value_{ value } {}

  constexpr friend auto operator<=>(time const lhs, time const rhs) noexcept
  {
    auto const delta = lhs.value_ - rhs.value_;
    return (delta < -epsilon ? -1 : (delta > epsilon ? 1 : 0));
  }

  constexpr friend auto operator==(time const lhs, time const rhs) noexcept { return (lhs <=> rhs) == 0; }

  constexpr explicit operator float() const noexcept { return value_; }

  constexpr explicit operator scalar() const noexcept { return scalar{ value_ }; }

private:
  float value_;
};


inline namespace literals {

  // Cppcheck doesn't seem to know what a user-defined literal is. I'm using Cppcheck 2.7.4.
  // cppcheck-suppress unknownMacro
  constexpr time operator""_s(unsigned long long const value) noexcept { return time{ static_cast<float>(value) }; }

  // Cppcheck doesn't seem to know what a user-defined literal is. I'm using Cppcheck 2.7.4.
  // cppcheck-suppress unknownMacro
  constexpr time operator""_s(long double const value) noexcept { return time{ static_cast<float>(value) }; }

}// namespace literals

}// namespace jam