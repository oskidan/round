#include <catch2/catch.hpp>

#include "jam/math/vector_io.hpp"
#include "jam/physics/acceleration.hpp"
#include "jam/physics/acceleration_io.hpp"
#include "jam/physics/velocity_io.hpp"

SCENARIO("Acceleration is represented as a vector.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("an acceleration a=(1, 2)")
  {
    jam::acceleration a{ 1_F, 2_F };
    THEN("it can be casted to a vector (1, 2)") { REQUIRE(static_cast<jam::vector>(a) == jam::vector{ 1_F, 2_F }); }
  }
}

SCENARIO("Adding an acceleration to an acceleration.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("an acceleration a=(1, 2)")
  {
    jam::acceleration a{ 1_F, 2_F };
    AND_GIVEN("an acceleration b=(3, 4)")
    {
      jam::acceleration b{ 3_F, 4_F };
      WHEN("I add them")
      {
        THEN("the resulting acceleration is (4, 6)") { REQUIRE((a + b) == jam::acceleration(4_F, 6_F)); }
      }
    }
  }
}

SCENARIO("Subtracting an acceleration from an acceleration.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("an acceleration a=(1, 2)")
  {
    jam::acceleration a{ 1_F, 2_F };
    AND_GIVEN("an acceleration b=(3, 4)")
    {
      jam::acceleration b{ 3_F, 4_F };
      WHEN("I subtract a from b")
      {
        THEN("the resulting acceleration is (2, 2)") { REQUIRE((b - a) == jam::acceleration(2_F, 2_F)); }
      }
    }
  }
}

SCENARIO("Acceleration over time gives velocity.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("an acceleration a=(1, 2)")
  {
    jam::acceleration a{ 1_F, 2_F };
    AND_GIVEN("a time interval t=2_s")
    {
      auto const t = 2_s;
      WHEN("I multiply a by t")
      {
        THEN("the resulting velocity is (2, 4)") { REQUIRE((a * t) == jam::velocity{ 2_F, 4_F }); }
      }
    }
  }
}