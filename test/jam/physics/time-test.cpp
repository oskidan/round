#include <catch2/catch.hpp>

#include "jam/physics/time.hpp"
#include "jam/physics/time_io.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Comparing time.", "[jam_physics]")
{
  GIVEN("a=0.001 and b=0.003")
  {
    jam::time a{ 0.001F };// NOLINT It's OK to use magic numbers in unit tests.
    jam::time b{ 0.003F };// NOLINT It's OK to use magic numbers in unit tests.
    WHEN("I compare them")
    {
      THEN("a != b") { REQUIRE(a != b); }
      THEN("a <= b") { REQUIRE(a <= b); }
      THEN("b >= a") { REQUIRE(b >= a); }
      THEN("a <  b") { REQUIRE(a < b); }
      THEN("b >  a") { REQUIRE(b > a); }
    }
  }

  GIVEN("a=0.001 and b=0.002")
  {
    jam::time a{ 0.001F };// NOLINT It's OK to use magic numbers in unit tests.
    jam::time b{ 0.002F };// NOLINT It's OK to use magic numbers in unit tests.
    WHEN("I compare them")
    {
      THEN("a != b") { REQUIRE(a == b); }
      THEN("a <= b") { REQUIRE(a <= b); }
      THEN("b >= a") { REQUIRE(b >= a); }
      THEN("not(a < b)") { REQUIRE_FALSE(a < b); }
      THEN("not(b > a)") { REQUIRE_FALSE(b > a); }
    }
  }
}

SCENARIO("Time literals.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("a literal 0.001_s")
  {
    THEN("it's the same as jam::time{0.001}")
    {
      REQUIRE(0.001_s == jam::time{ 0.001F });// NOLINT It's OK to use magic numbers in unit tests.
    }
  }
}

SCENARIO("Getting the raw value of a time instance.", "[jam_physics]")
{
  using namespace jam::literals;
  GIVEN("a time t=0.001_s")
  {
    auto const t = 0.001_s;
    THEN("its raw value is 0.001F")
    {
      REQUIRE(static_cast<float>(t) == 0.001F);// NOLINT It's OK to use magic numbers in unit tests.
    }
  }
}