#pragma once
#include "jam/math/vector.hpp"
#include "jam/physics/time.hpp"

namespace jam {

// I represent the rate of change of object's position with resepect to time, measured in meters per second.
struct [[nodiscard]] velocity final
{
  constexpr explicit velocity(vector const value) noexcept : value_{ value } {}

  constexpr velocity(scalar const x, scalar const y) noexcept : value_{ x, y } {}

  // TODO:
  //  Think about a meanignful way of comparing velocities. They can be compared either by their magnitude (speed) or
  //  by their direction. I guess that the problem is deeper than it seems, should revisit how I compare jam::vectors.
  //  Currently they are compared lexographically.
  //
  // Alternatives:
  //  - Compare vectors by magnitude.
  //  - Compare vectors by direction (where a direciton is represented as a CCW angle).
  //
  // For the time being, I'm going to be handwavy about this issue.

  constexpr friend bool operator==(velocity const lhs, velocity const rhs) noexcept { return lhs.value_ == rhs.value_; }

  constexpr explicit operator vector() const noexcept { return value_; }

  constexpr velocity &operator+=(velocity const rhs) noexcept
  {
    value_ += rhs.value_;
    return *this;
  }

  constexpr velocity &operator-=(velocity const rhs) noexcept
  {
    value_ -= rhs.value_;
    return *this;
  }

  constexpr velocity &operator*=(scalar const rhs) noexcept
  {
    value_ *= rhs;
    return *this;
  }

private:
  vector value_;
};

constexpr velocity operator+(velocity const lhs, velocity const rhs) noexcept { return velocity{ lhs } += rhs; }
constexpr velocity operator-(velocity const lhs, velocity const rhs) noexcept { return velocity{ lhs } -= rhs; }

constexpr velocity operator*(velocity const lhs, scalar const rhs) noexcept { return velocity{ lhs } *= rhs; }

// Returns the distance in meters traveled by the object in the specified time.
constexpr vector operator*(velocity const lhs, time const rhs) noexcept
{
  return static_cast<vector>(lhs) * static_cast<scalar>(rhs);
}

}// namespace jam