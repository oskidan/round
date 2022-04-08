#pragma once
#include "jam/math/point.hpp"
#include "jam/math/scalar.hpp"
#include "jam/physics/acceleration.hpp"
#include "jam/physics/force.hpp"
#include "jam/physics/mass.hpp"

#include <utility>

namespace jam {

// I am a plint-like particle. I'm dimensionless, i.e. I do not take up space. Use me as a representation of any object
// whenver its size, shape, and structure are irrelevant in a given context.
struct [[nodiscard]] particle final
{
  constexpr particle(point const position, mass const mass) noexcept : position_{ position }, mass_{ mass } {}

  constexpr void apply(force const force) noexcept { force_ += force; }

  // Updates the particle by integrating Newton's equations of motion. This method implements the numerical method known
  // as Verlet integration.
  constexpr void update(time const dt) noexcept
  {
    // NOLINTNEXTLINE IMHO, constants like 0.5 should be allowed. They make a lot of sense for a human reader.
    position_ = position_ + velocity_ * dt + acceleration_ * dt * dt * 0.5_F;

    // Note that the force will be reset to zero. This is the way I represent impulses. If you want to have a continuous
    // force, such as gravity, keep applying it in every simulation step.
    auto const new_acceleration = std::exchange(force_, force{ 0_F, 0_F }) / mass_;

    // NOLINTNEXTLINE IMHO, constants like 0.5 should be allowed. They make a lot of sense for a human reader.
    velocity_ = velocity_ + (acceleration_ + new_acceleration) * dt * 0.5_F;

    // Damping is required to remove energy added through numerical instability in the integrator.
    constexpr auto linear_damping = 0.999_F;
    velocity_ *= linear_damping;

    acceleration_ = new_acceleration;
  }

  // Returns where the particle is located in space. The returned value is in meters.
  constexpr point position() const noexcept { return position_; }

  constexpr mass mass() const noexcept { return mass_; }

  constexpr void move_to(point const position) noexcept { position_ = position; }

  constexpr void move_to(scalar const x, scalar const y) noexcept { move_to(point{ x, y }); }

private:
  point position_;

  velocity velocity_{ 0_F, 0_F };

  acceleration acceleration_{ 0_F, 0_F };

  force force_{ 0_F, 0_F };

  struct mass mass_;
};

}// namespace jam