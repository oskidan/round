#include <catch2/catch.hpp>

#include "jam/physics/acceleration.hpp"
#include "jam/physics/force.hpp"

SCENARIO("Force is represented as a vector.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("a force f=(1, 2)")
  {
    jam::force f{ 1_F, 2_F };
    WHEN("I convert it to a vector")
    {
      THEN("the resulting vector is (1, 2)") { REQUIRE(static_cast<jam::vector>(f) == jam::vector{ 1_F, 2_F }); }
    }
  }
}

SCENARIO("Adding a force to a force gives a force.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("a force f=(1, 2)")
  {
    jam::force f{ 1_F, 2_F };
    AND_GIVEN("a force g=(3 ,4)")
    {
      jam::force g{ 3_F, 4_F };
      WHEN("I add them")
      {
        THEN("the resulting force is (4, 6)") { REQUIRE((f + g) == jam::force{ 4_F, 6_F }); }
      }
    }
  }
}

SCENARIO("Subtracting a force from a force gives a force.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("a force f=(1, 2)")
  {
    jam::force f{ 1_F, 2_F };
    AND_GIVEN("a force g=(3 ,4)")
    {
      jam::force g{ 3_F, 4_F };
      WHEN("I subtract f from g")
      {
        THEN("the resulting force is (2, 2)") { REQUIRE((g - f) == jam::force{ 2_F, 2_F }); }
      }
    }
  }
}

SCENARIO("Applying a force to a mass gives an acceleration.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("a force f=(1, 2) kg·m/s²")
  {
    jam::force f{ 1_F, 2_F };
    AND_GIVEN("a mass m=2_kg")
    {
      auto const m = 2_kg;
      WHEN("I apply the force to the mass")
      {
        THEN("the resulting acceleration is (0.5, 1) m/s²")
        {
          REQUIRE(f / m == jam::acceleration{ 0.5_F, 1_F });// NOLINT It's OK to use magic numbers in unit tests.
        }
      }
    }
  }
}