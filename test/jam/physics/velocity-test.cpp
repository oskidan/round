#include <catch2/catch.hpp>

#include "jam/math/vector_io.hpp"
#include "jam/physics/velocity.hpp"
#include "jam/physics/velocity_io.hpp"

SCENARIO("Velocity is represented as a vector.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("a vector v=(1, 2)")
  {
    jam::vector v{ 1_F, 2_F };
    WHEN("I construct a velocity u with that vector")
    {
      jam::velocity u{ v };
      THEN("the raw value of u is equal to v") { REQUIRE(static_cast<jam::vector>(u) == v); }
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Adding velocities.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("a velocity v=(1, 2)")
  {
    jam::velocity v{ 1_F, 2_F };
    AND_GIVEN("a velocity u=(3, 4)")
    {
      jam::velocity u{ 3_F, 4_F };
      WHEN("I add v to u")
      {
        THEN("the resulting velocity is (4, 6)") { REQUIRE((v + u) == jam::velocity{ 4_F, 6_F }); }
      }
      WHEN("I add u to v")
      {
        THEN("the resulting velocity is (4, 6)") { REQUIRE((u + v) == jam::velocity{ 4_F, 6_F }); }
      }
    }
  }
}

SCENARIO("Velocity over time gives displacement.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("a velocity v=(1, 2)")
  {
    jam::velocity v{ 1_F, 2_F };
    AND_GIVEN("the body travelled for t=2s")
    {
      auto const t = 2_s;
      WHEN("I multiply v by t")
      {
        auto const displacement = v * t;
        THEN("the displacement (distance traveled) is (2, 4)") { REQUIRE(displacement == jam::vector{ 2_F, 4_F }); }
      }
    }
  }
}
