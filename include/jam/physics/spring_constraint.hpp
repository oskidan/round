#pragma once
#include "jam/physics/particle.hpp"

namespace jam {

struct [[nodiscard]] spring_constraint final
{
  // NOLINTNEXTLINE(bugprone-easily-swappable-parameters): it's okay to swap a and b, the result is order independent.
  constexpr spring_constraint(particle &a, particle &b, scalar stiffness, scalar relaxed_length) noexcept
    : a_{ &a }, b_{ &b }, stiffness_{ stiffness }, relaxed_length_{ relaxed_length }
  {}

  constexpr spring_constraint(particle &a, particle &b, scalar stiffness) noexcept
    : spring_constraint{ a, b, stiffness, length(a.position() - b.position()) }
  {}

  constexpr spring_constraint(particle &a, particle &b) noexcept : spring_constraint{ a, b, 1.0_F } {}

  void resolve_constraint() const noexcept
  {
    auto const vector_ab = a_->position() - b_->position();
    auto const displacement = length(vector_ab) - relaxed_length_;
    auto const force = jam::force{ normalized(vector_ab) * stiffness_ * displacement };
    // clang-format off
    a_->apply(-force);
    b_->apply( force);
    // clang-format on
  }

private:
  particle *a_;
  particle *b_;
  scalar stiffness_;
  scalar relaxed_length_;
};

}// namespace jam