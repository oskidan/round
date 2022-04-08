#pragma once
#include <cmath>

#include "jam/math/scalar.hpp"

namespace jam {

// I am an element of a vector space.
struct [[nodiscard]] vector final
{
  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters) Vectors are idiomatic. X always goes first, Y goes second.
  constexpr vector(scalar const x, scalar const y) noexcept : x_{ x }, y_{ y } {}

  constexpr friend auto operator<=>(vector const lhs, vector const rhs) noexcept
  {
    // The libc++ that is being shppied with Apple clang version 13.1.6 doesn't fully conform to the standard.
    // It does not implement the `operator<=>` for `std::tuple`. Because of that I cannot use `std::tie` here.
    auto const x_comparison = lhs.x_ <=> rhs.x_;
    return x_comparison == 0 ? lhs.y_ <=> rhs.y_ : x_comparison;
  }

  constexpr friend auto operator==(vector const lhs, vector const rhs) noexcept { return (lhs <=> rhs) == 0; }

  constexpr scalar x() const noexcept { return x_; }
  constexpr scalar y() const noexcept { return y_; }

  constexpr vector &operator+=(scalar const rhs) noexcept
  {
    x_ += rhs;
    y_ += rhs;
    return *this;
  }

  constexpr vector &operator-=(scalar const rhs) noexcept
  {
    x_ -= rhs;
    y_ -= rhs;
    return *this;
  }

  constexpr vector &operator*=(scalar const rhs) noexcept
  {
    x_ *= rhs;
    y_ *= rhs;
    return *this;
  }

  constexpr vector &operator/=(scalar const rhs) noexcept
  {
    x_ /= rhs;
    y_ /= rhs;
    return *this;
  }

  constexpr vector &operator+=(vector const rhs) noexcept
  {
    x_ += rhs.x();
    y_ += rhs.y();
    return *this;
  }

  constexpr vector &operator-=(vector const rhs) noexcept
  {
    x_ -= rhs.x();
    y_ -= rhs.y();
    return *this;
  }

private:
  scalar x_;
  scalar y_;
};

constexpr vector operator-(vector const rhs) noexcept { return vector{ -rhs.x(), -rhs.y() }; }
constexpr vector operator+(vector const rhs) noexcept { return vector{ +rhs.x(), +rhs.y() }; }

constexpr vector operator+(vector const lhs, scalar const rhs) noexcept { return vector{ lhs } += rhs; }
constexpr vector operator-(vector const lhs, scalar const rhs) noexcept { return vector{ lhs } -= rhs; }

constexpr vector operator*(vector const lhs, scalar const rhs) noexcept { return vector{ lhs } *= rhs; }
constexpr vector operator/(vector const lhs, scalar const rhs) noexcept { return vector{ lhs } /= rhs; }

constexpr vector operator+(vector const lhs, vector const rhs) noexcept { return vector{ lhs } += rhs; }
constexpr vector operator-(vector const lhs, vector const rhs) noexcept { return vector{ lhs } -= rhs; }

constexpr scalar operator*(vector const lhs, vector const rhs) noexcept
{
  return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

constexpr scalar length(vector const v) noexcept { return sqrt(v * v); }

constexpr vector normalized(vector const v) noexcept
{
  if (auto const magnitude = length(v); magnitude != 0_F) { return vector{ v } /= magnitude; }
  return v;
}

}// namespace jam