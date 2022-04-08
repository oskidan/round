#pragma once
#include "jam/math/vector.hpp"

namespace jam {

// I am an entity that has a location in space or on a plane, but has no extent.
struct [[nodiscard]] point final
{
  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters) Points are idiomatic. X always goes first, Y goes second.
  constexpr point(scalar const x, scalar const y) noexcept : x_{ x }, y_{ y } {}

  constexpr friend auto operator<=>(point const lhs, point const rhs) noexcept
  {
    // The libc++ that is being shppied with Apple clang version 13.1.6 doesn't fully conform to the standard.
    // It does not implement the `operator<=>` for `std::tuple`. Because of that I cannot use `std::tie` here.
    auto const x_comparison = lhs.x_ <=> rhs.x_;
    return x_comparison == 0 ? lhs.y_ <=> rhs.y_ : x_comparison;
  }

  constexpr friend auto operator==(point const lhs, point const rhs) noexcept { return (lhs <=> rhs) == 0; }

  constexpr scalar x() const noexcept { return x_; }
  constexpr scalar y() const noexcept { return y_; }

  constexpr point &operator+=(scalar const rhs) noexcept
  {
    x_ += rhs;
    y_ += rhs;
    return *this;
  }

  constexpr point &operator-=(scalar const rhs) noexcept
  {
    x_ -= rhs;
    y_ -= rhs;
    return *this;
  }

  constexpr point &operator*=(scalar const rhs) noexcept
  {
    x_ *= rhs;
    y_ *= rhs;
    return *this;
  }

  constexpr point &operator/=(scalar const rhs) noexcept
  {
    x_ /= rhs;
    y_ /= rhs;
    return *this;
  }

  constexpr point &operator+=(vector const rhs) noexcept
  {
    x_ += rhs.x();
    y_ += rhs.y();
    return *this;
  }

  constexpr point &operator-=(vector const rhs) noexcept
  {
    x_ -= rhs.x();
    y_ -= rhs.y();
    return *this;
  }

  constexpr explicit operator vector() const noexcept { return vector{ x(), y() }; }

private:
  scalar x_;
  scalar y_;
};

constexpr point operator+(point const lhs, scalar const rhs) noexcept { return point{ lhs } += rhs; }
constexpr point operator-(point const lhs, scalar const rhs) noexcept { return point{ lhs } -= rhs; }

constexpr point operator*(point const lhs, scalar const rhs) noexcept { return point{ lhs } *= rhs; }
constexpr point operator/(point const lhs, scalar const rhs) noexcept { return point{ lhs } /= rhs; }

constexpr point operator+(point const lhs, vector const rhs) noexcept { return point{ lhs } += rhs; }
constexpr point operator-(point const lhs, vector const rhs) noexcept { return point{ lhs } -= rhs; }

constexpr vector operator-(point const lhs, point const rhs) noexcept
{
  return vector{ lhs.x() - rhs.x(), lhs.y() - rhs.y() };
}

}// namespace jam