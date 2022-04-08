#include <catch2/catch.hpp>

#include "jam/math/point.hpp"
#include "jam/math/point_io.hpp"
#include "jam/math/vector_io.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("A point is a pair of X and Y coordinates.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a pair of scalars a=1 and b=2")
  {
    auto const a = 1_F;
    auto const b = 2_F;
    WHEN("I construct a point p(a, b)")
    {
      jam::point p{ a, b };
      THEN("the X coodinate of p is equal to a") { REQUIRE(p.x() == a); }
      THEN("the Y coodinate of p is equal to b") { REQUIRE(p.y() == b); }
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Comparing points.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("point a=(0.001, 0.003) and b=(0.003, 0.001)")
  {
    // It's OK to use magic numbers in unit tests.
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    jam::point a{ 0.001_F, 0.003_F };
    // It's OK to use magic numbers in unit tests.
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    jam::point b{ 0.003_F, 0.001_F };
    WHEN("I compare them")
    {
      THEN("a != b") { REQUIRE(a != b); }
      THEN("a <= b") { REQUIRE(a <= b); }
      THEN("b >= a") { REQUIRE(b >= b); }
      THEN("a < b") { REQUIRE(a < b); }
      THEN("b > a") { REQUIRE(a < b); }
    }
  }
}

SCENARIO("Adding a scalar to a point.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a pont p=(1, 2)")
  {
    jam::point p{ 1_F, 2_F };
    AND_GIVEN("a scalar t=3")
    {
      auto const t = 3_F;
      WHEN("I add t to p")
      {
        auto const result = p + t;
        THEN("the resulting point is (4, 5)") { REQUIRE(result == jam::point{ 4_F, 5_F }); }
      }
    }
  }
}

SCENARIO("Subtracting a scalar from a point.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a point p=(1, 2)")
  {
    jam::point p{ 1_F, 2_F };
    AND_GIVEN("a scalar t=3")
    {
      auto const t = 3_F;
      WHEN("I subtract t from v")
      {
        auto const result = p - t;
        THEN("the resulting point is (-2, -1)") { REQUIRE(result == jam::point{ -2_F, -1_F }); }
      }
    }
  }
}

SCENARIO("Multiplying a point by a scalar.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a point p=(1, 2)")
  {
    jam::point p{ 1_F, 2_F };
    AND_GIVEN("a scalar t=3")
    {
      auto const t = 3_F;
      WHEN("I multiply v by t")
      {
        auto const result = p * t;
        THEN("the resulting point is (3, 6)") { REQUIRE(result == jam::point{ 3_F, 6_F }); }
      }
    }
  }
}

SCENARIO("Dividing a point by a scalar.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a point p=(1, 2)")
  {
    jam::point p{ 1_F, 2_F };
    AND_GIVEN("a scalar t=3")
    {
      auto const t = 3_F;
      WHEN("I divide v by t")
      {
        auto const result = p / t;
        THEN("the resulting point is (0.333, 0.666)")
        {
          REQUIRE(result == jam::point{ 0.333_F, 0.666_F });// NOLINT It's OK to use magic numbers in unit tests.
        }
      }
    }
  }
}

SCENARIO("Adding a vector to a point gives a point.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a point p=(1, 2)")
  {
    jam::point p{ 1_F, 2_F };
    AND_GIVEN("a vector v=(3, 4)")
    {
      jam::vector v{ 3_F, 4_F };
      WHEN("I add v to p")
      {
        auto const result = p + v;
        THEN("the resulting point is (4, 6)") { REQUIRE(result == jam::point{ 4_F, 6_F }); }
      }
    }
  }
}

SCENARIO("Subtracting a vector from a point gives a point.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a point p=(1, 2)")
  {
    jam::point p{ 1_F, 2_F };
    AND_GIVEN("a vector v=(3, 4)")
    {
      jam::vector v{ 3_F, 4_F };
      WHEN("I subtract v from p")
      {
        auto const result = p - v;
        THEN("the resulting point is (-2, -2)") { REQUIRE(result == jam::point{ -2_F, -2_F }); }
      }
    }
  }
}

SCENARIO("Subtracting a point from a point gives a vector.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a point p=(1, 2)")
  {
    jam::point p{ 1_F, 2_F };
    AND_GIVEN("a point q=(3, 4)")
    {
      jam::point q{ 3_F, 4_F };
      WHEN("I subtract p from q")
      {
        auto const result = q - p;
        THEN("the resulting vector is (2, 2)") { REQUIRE(result == jam::vector{ 2_F, 2_F }); }
      }
    }
  }
}