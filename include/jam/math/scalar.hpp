#pragma once
#include <cmath>
#include <iosfwd>

namespace jam {

// I am an element of a field, which is used to define a vector space.
struct [[nodiscard]] scalar final
{
  constexpr static inline auto epsilon = 0.001F;

  constexpr explicit scalar(float const value) noexcept : value_{ value } {}

  constexpr friend auto operator<=>(scalar const lhs, scalar const rhs) noexcept
  {
    auto const delta = lhs.value_ - rhs.value_;
    return (delta < -epsilon ? -1 : (delta > epsilon ? 1 : 0));
  }

  constexpr friend auto operator==(scalar const lhs, scalar const rhs) noexcept { return (lhs <=> rhs) == 0; }

  constexpr scalar &operator+=(scalar const rhs) noexcept
  {
    value_ += rhs.value_;
    return *this;
  }

  constexpr scalar &operator-=(scalar const rhs) noexcept
  {
    value_ -= rhs.value_;
    return *this;
  }

  constexpr scalar &operator*=(scalar const rhs) noexcept
  {
    value_ *= rhs.value_;
    return *this;
  }

  constexpr scalar &operator/=(scalar const rhs) noexcept
  {
    value_ /= rhs.value_;
    return *this;
  }

  constexpr scalar &operator++() noexcept
  {
    value_ += 1.F;
    return *this;
  }

  constexpr scalar operator++(int) noexcept
  {
    auto result = *this;
    value_ += 1.F;
    return result;
  }

  constexpr explicit operator float() const noexcept { return value_; }

private:
  float value_;
};

constexpr scalar operator-(scalar const rhs) noexcept { return scalar{ -static_cast<float>(rhs) }; }
constexpr scalar operator+(scalar const rhs) noexcept { return scalar{ +static_cast<float>(rhs) }; }

constexpr scalar operator+(scalar const lhs, scalar const rhs) noexcept { return scalar{ lhs } += rhs; }
constexpr scalar operator-(scalar const lhs, scalar const rhs) noexcept { return scalar{ lhs } -= rhs; }

constexpr scalar operator*(scalar const lhs, scalar const rhs) noexcept { return scalar{ lhs } *= rhs; }
constexpr scalar operator/(scalar const lhs, scalar const rhs) noexcept { return scalar{ lhs } /= rhs; }

constexpr scalar sqrt(scalar const s) noexcept { return scalar{ std::sqrt(static_cast<float>(s)) }; }

constexpr scalar abs(scalar const s) noexcept { return std::signbit(static_cast<float>(s)) ? -s : s; }

inline namespace literals {

  // The "_F" literal may look strange to some. What does it stand for, Farenheight?
  // This literal is like the built-in "F" literal, but yields an instance of scalar. Consider: 0.03F vs 0.03_F.

  // Cppcheck doesn't seem to know what a user-defined literal is. I'm using Cppcheck 2.7.4.
  // cppcheck-suppress unknownMacro
  constexpr scalar operator""_F(unsigned long long const value) noexcept { return scalar{ static_cast<float>(value) }; }

  // Cppcheck doesn't seem to know what a user-defined literal is. I'm using Cppcheck 2.7.4.
  // cppcheck-suppress unknownMacro
  constexpr scalar operator""_F(long double const value) noexcept { return scalar{ static_cast<float>(value) }; }

}// namespace literals

}// namespace jam