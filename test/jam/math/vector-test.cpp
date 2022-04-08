#include <catch2/catch.hpp>

#include "jam/math/scalar_io.hpp"
#include "jam/math/vector.hpp"
#include "jam/math/vector_io.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("A vector is a pair of X and Y coordinates.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a pair of scalars a=1 and b=2")
  {
    auto const a = 1_F;
    auto const b = 2_F;
    WHEN("I construct a vector v(a, b)")
    {
      jam::vector v{ a, b };
      THEN("the X coodinate of the vector is equal to a") { REQUIRE(v.x() == a); }
      THEN("the Y coodinate of the vector is equal to b") { REQUIRE(v.y() == b); }
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Comparing vectors.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("vector a=(0.001, 0.003) and b=(0.003, 0.001)")
  {
    // It's OK to use magic numbers in unit tests.
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    jam::vector a{ 0.001_F, 0.003_F };
    // It's OK to use magic numbers in unit tests.
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    jam::vector b{ 0.003_F, 0.001_F };
    WHEN("I compare them")
    {
      THEN("a != b") { REQUIRE(a != b); }
      THEN("a <= b") { REQUIRE(a <= b); }
      THEN("b >= a") { REQUIRE(b >= b); }
      THEN("a < b") { REQUIRE(a < b); }
      THEN("b > a") { REQUIRE(b > a); }
    }
  }
}

SCENARIO("Adding a scalar to a vector.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a vector v=(1, 2)")
  {
    jam::vector v{ 1_F, 2_F };
    AND_GIVEN("a scalar t=3")
    {
      auto const t = 3_F;
      WHEN("I add t to v")
      {
        auto const result = v + t;
        THEN("the resulting vector is (4, 5)") { REQUIRE(result == jam::vector{ 4_F, 5_F }); }
      }
    }
  }
}

SCENARIO("Subtracting a scalar from a vector.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a vector v=(1, 2)")
  {
    jam::vector v{ 1_F, 2_F };
    AND_GIVEN("a scalar t=3")
    {
      auto const t = 3_F;
      WHEN("I subtract t from v")
      {
        auto const result = v - t;
        THEN("the resulting vector is (-2, -1)") { REQUIRE(result == jam::vector{ -2_F, -1_F }); }
      }
    }
  }
}

SCENARIO("Multiplying a vector by a scalar.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a vector v=(1, 2)")
  {
    jam::vector v{ 1_F, 2_F };
    AND_GIVEN("a scalar t=3")
    {
      auto const t = 3_F;
      WHEN("I multiply v by t")
      {
        auto const result = v * t;
        THEN("the resulting vector is (3, 6)") { REQUIRE(result == jam::vector{ 3_F, 6_F }); }
      }
    }
  }
}

SCENARIO("Dividing a vector by a scalar.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a vector v=(1, 2)")
  {
    jam::vector v{ 1_F, 2_F };
    AND_GIVEN("a scalar t=3")
    {
      auto const t = 3_F;
      WHEN("I divide v by t")
      {
        auto const result = v / t;
        THEN("the resulting vector is (0.333, 0.666)")
        {
          REQUIRE(result == jam::vector{ 0.333_F, 0.666_F });// NOLINT It's OK to use magic numbers in unit tests.
        }
      }
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Adding a vector to a vector.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a vector v=(1, 2)")
  {
    jam::vector v{ 1_F, 2_F };
    AND_GIVEN("a vector u=(3, 4)")
    {
      jam::vector u{ 3_F, 4_F };
      WHEN("I add u to v")
      {
        auto const result = v + u;
        THEN("the resulting vector is (4, 6)") { REQUIRE(result == jam::vector{ 4_F, 6_F }); }
      }
      WHEN("I add v to u")
      {
        auto const result = u + v;
        THEN("the resulting vector is (4, 6)") { REQUIRE(result == jam::vector{ 4_F, 6_F }); }
      }
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Subtracting a vector from a vector.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a vector v=(1, 2)")
  {
    jam::vector v{ 1_F, 2_F };
    AND_GIVEN("a vector u=(3, 4)")
    {
      jam::vector u{ 3_F, 4_F };
      WHEN("I subtract u from v")
      {
        auto const result = v - u;
        THEN("the resulting vector is (-2, -2)") { REQUIRE(result == jam::vector{ -2_F, -2_F }); }
      }
      WHEN("I subtract v from u")
      {
        auto const result = u - v;
        THEN("the resulting vector is (2, 2)") { REQUIRE(result == jam::vector{ 2_F, 2_F }); }
      }
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Scalar product of two vectors.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a vector v=(3, 4)")
  {
    jam::vector v{ 3_F, 4_F };
    AND_GIVEN("a vector u=(3, 4)")
    {
      jam::vector u{ 3_F, 4_F };
      WHEN("I multiply v by u")
      {
        auto const result = v * u;
        THEN("the resulting scalar is 25") { REQUIRE(result == 25_F); }
      }
      WHEN("I multiply u by v")
      {
        auto const result = u * v;
        THEN("the resulting scalar is 25") { REQUIRE(result == 25_F); }
      }
    }
  }
}

SCENARIO("Vector length.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a vector v=(3, 4)")
  {
    jam::vector v{ 3_F, 4_F };
    THEN("its length is 5") { REQUIRE(length(v) == 5_F); }
  }
}