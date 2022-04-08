#pragma once
#include "jam/physics/velocity.hpp"

namespace jam {

// I am the rate of change of the velocity of an object with respect to time, measured in m/s².
struct [[nodiscard]] acceleration final
{
  constexpr explicit acceleration(vector const value) noexcept : value_{ value } {}

  constexpr acceleration(scalar const x, scalar const y) noexcept : value_{ x, y } {}

  constexpr friend bool operator==(acceleration const lhs, acceleration const rhs) noexcept
  {
    return lhs.value_ == rhs.value_;
  }

  constexpr explicit operator vector() const noexcept { return value_; }

  constexpr acceleration &operator+=(acceleration const rhs) noexcept
  {
    value_ += rhs.value_;
    return *this;
  }

  constexpr acceleration &operator-=(acceleration const rhs) noexcept
  {
    value_ -= rhs.value_;
    return *this;
  }

private:
  vector value_;
};

constexpr acceleration operator+(acceleration const lhs, acceleration const rhs) noexcept
{
  return acceleration{ lhs } += rhs;
}
constexpr acceleration operator-(acceleration const lhs, acceleration const rhs) noexcept
{
  return acceleration{ lhs } -= rhs;
}

// Returns the velocity in meters per second gained by the object in the specified time.
constexpr velocity operator*(acceleration const lhs, time const rhs) noexcept
{
  return velocity{ static_cast<vector>(lhs) * static_cast<scalar>(rhs) };
}

}// namespace jam