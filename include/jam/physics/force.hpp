#pragma once
#include "jam/math/scalar.hpp"
#include "jam/physics/acceleration.hpp"
#include "jam/physics/mass.hpp"

namespace jam {

// I am an influence that can change the motion of an object. I can cause an object with mass to change its velocity.
// I am measured in newtons (kg·m/s²).
struct [[nodiscard]] force final
{
  constexpr explicit force(vector const value) noexcept : value_{ value } {}

  constexpr force(scalar const x, scalar const y) noexcept : value_{ x, y } {}

  constexpr friend bool operator==(force const lhs, force const rhs) noexcept { return lhs.value_ == rhs.value_; }

  constexpr explicit operator vector() const noexcept { return value_; }

  constexpr force &operator+=(force const rhs) noexcept
  {
    value_ += rhs.value_;
    return *this;
  }

  constexpr force &operator-=(force const rhs) noexcept
  {
    value_ -= rhs.value_;
    return *this;
  }

  constexpr force &operator*=(scalar const rhs) noexcept
  {
    value_ *= rhs;
    return *this;
  }

  constexpr force &operator/=(scalar const rhs) noexcept
  {
    value_ /= rhs;
    return *this;
  }

private:
  vector value_;
};

constexpr force operator-(force const rhs) noexcept { return force{ -static_cast<vector>(rhs) }; }
constexpr force operator+(force const rhs) noexcept { return force{ +static_cast<vector>(rhs) }; }

constexpr force operator+(force const lhs, force const rhs) noexcept { return force{ lhs } += rhs; }
constexpr force operator-(force const lhs, force const rhs) noexcept { return force{ lhs } -= rhs; }

constexpr force operator*(force const lhs, scalar const rhs) noexcept { return force{ lhs } *= rhs; }
constexpr force operator/(force const lhs, scalar const rhs) noexcept { return force{ lhs } /= rhs; }

// Returns the accelration gained by the object to which the specified force is applied.
constexpr acceleration operator/(force const lhs, mass const rhs) noexcept
{
  return rhs == infinite_mass ? acceleration{ 0_F, 0_F }
                              : acceleration{ static_cast<vector>(lhs) / static_cast<scalar>(rhs) };
}

}// namespace jam