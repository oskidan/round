#pragma once
#include "jam/math/scalar.hpp"

namespace jam {

// I am the quantity of matter in a physical body, measured in kilograms.
struct [[nodiscard]] mass final
{
  // Precision of 1 gram.
  constexpr static inline auto epsilon = 0.001F;

  constexpr explicit mass(float const value) noexcept : value_{ value } {}

  constexpr friend auto operator<=>(mass const lhs, mass const rhs) noexcept
  {
    auto const delta = lhs.value_ - rhs.value_;
    return (delta < -epsilon ? -1 : (delta > epsilon ? 1 : 0));
  }

  constexpr friend auto operator==(mass const lhs, mass const rhs) noexcept { return (lhs <=> rhs) == 0; }

  constexpr explicit operator float() const noexcept { return value_; }

  constexpr explicit operator scalar() const noexcept { return scalar{ value_ }; }

  constexpr mass &operator+=(mass const rhs) noexcept
  {
    value_ += rhs.value_;
    return *this;
  }

  constexpr mass &operator-=(mass const rhs) noexcept
  {
    value_ -= rhs.value_;
    return *this;
  }

private:
  float value_;
};

// To make calculations simpler, infinite mass is represented as 0. Infinite mass objects are not influenced by forces.
constexpr inline mass infinite_mass{ 0.F };

constexpr mass operator+(mass const lhs, mass const rhs) noexcept { return mass{ lhs } += rhs; }
constexpr mass operator-(mass const lhs, mass const rhs) noexcept { return mass{ lhs } -= rhs; }

constexpr scalar operator/(mass const lhs, mass const rhs) noexcept
{
  return static_cast<scalar>(lhs) / static_cast<scalar>(rhs);
}

inline namespace literals {

  // Cppcheck doesn't seem to know what a user-defined literal is. I'm using Cppcheck 2.7.4.
  // cppcheck-suppress unknownMacro
  constexpr mass operator""_kg(unsigned long long const value) noexcept { return mass{ static_cast<float>(value) }; }

  // Cppcheck doesn't seem to know what a user-defined literal is. I'm using Cppcheck 2.7.4.
  // cppcheck-suppress unknownMacro
  constexpr mass operator""_kg(long double const value) noexcept { return mass{ static_cast<float>(value) }; }

}// namespace literals

}// namespace jam