#include <catch2/catch.hpp>

#include "jam/math/scalar.hpp"
#include "jam/math/scalar_io.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Comparing scalars.", "[jam_math]")
{
  GIVEN("a=0.001 and b=0.003")
  {
    jam::scalar a{ 0.001F };// NOLINT It's OK to use magic numbers in unit tests.
    jam::scalar b{ 0.003F };// NOLINT It's OK to use magic numbers in unit tests.
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
    jam::scalar a{ 0.001F };// NOLINT It's OK to use magic numbers in unit tests.
    jam::scalar b{ 0.002F };// NOLINT It's OK to use magic numbers in unit tests.
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

SCENARIO("Constructing scalars with _F literals.", "[jam_math]")
{
  using namespace jam::literals;
  GIVEN("a literal 0.001_F")
  {
    THEN("it's the same as jam::scalar{0.001}")
    {
      // It's OK to use magic numbers in unit test.
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      REQUIRE(0.001_F == jam::scalar{ 0.001F });
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Negating scalars.", "[jam_math]")
{
  GIVEN("a=-0.002 and b=0.002")
  {
    jam::scalar a{ -0.002F };// NOLINT It's OK to use magic numbers in unit tests.
    jam::scalar b{ 0.002F };// NOLINT It's OK to use magic numbers in unit tests.
                            //  -- Bart Simpson
    WHEN("I compare a to -b")
    {
      THEN("they should be equal") { REQUIRE(a == -b); }
    }
    WHEN("I compare -a to b")
    {
      THEN("they should be equal") { REQUIRE(-a == b); }
    }
  }
}

SCENARIO("Scalar addition.", "[jam_math]")
{
  GIVEN("a=0.002 and b=0.003")
  {
    jam::scalar a{ 0.002F };// NOLINT It's OK to use magic numbers in unit tests.
    jam::scalar b{ 0.003F };// NOLINT It's OK to use magic numbers in unit tests.
    WHEN("I add them")
    {
      auto const sum = a + b;
      THEN("their sum should be equal to 0.005")
      {
        REQUIRE(sum == jam::scalar{ 0.005F });// NOLINT It's OK to use magic numbers in unit tests.
      }
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity) False positive cognitive complexity due to macros.
SCENARIO("Scalar subtraction.", "[jam_math]")
{
  GIVEN("a=0.002 and b=0.003")
  {
    jam::scalar a{ 0.002F };// NOLINT It's OK to use magic numbers in unit tests.
    jam::scalar b{ 0.003F };// NOLINT It's OK to use magic numbers in unit tests.
    WHEN("I subtract b from a")
    {
      auto const subtraction_result = a - b;
      THEN("the result should be equal to -0.001")
      {
        REQUIRE(subtraction_result == jam::scalar{ -0.001F });// NOLINT It's OK to use magic numbers in unit tests.
      }
    }
    WHEN("I subtract a from b")
    {
      auto const subtraction_result = b - a;
      THEN("the result should be equal to 0.001")
      {
        REQUIRE(subtraction_result == jam::scalar{ 0.001F });// NOLINT It's OK to use magic numbers in unit tests.
      }
    }
  }
}

SCENARIO("Scalar multiplication.", "[jam_math]")
{
  GIVEN("a=2.0 and b=0.003")
  {
    jam::scalar a{ 2.F };// NOLINT It's OK to use magic numbers in unit tests.
    jam::scalar b{ 0.003F };// NOLINT It's OK to use magic numbers in unit tests.
    WHEN("I multiply them")
    {
      auto const multiplication_result = a * b;
      THEN("the result should be equal to 0.006")
      {
        REQUIRE(multiplication_result == jam::scalar{ 0.006F });// NOLINT It's OK to use magic numbers in unit tests.
      }
    }
  }
}

SCENARIO("Scalar division.", "[jam_math]")
{
  GIVEN("a=2.0 and b=0.002")
  {
    jam::scalar a{ 2.F };// NOLINT It's OK to use magic numbers in unit tests.
    jam::scalar b{ 0.002F };// NOLINT It's OK to use magic numbers in unit tests.
    WHEN("I divide a by b")
    {
      auto const division_result = a / b;
      THEN("the result should be equal to 1000.0")
      {
        REQUIRE(division_result == jam::scalar{ 1000.F });// NOLINT It's OK to use magic numbers in unit tests.
      }
    }
  }
}

SCENARIO("Scalar square root.", "[jam_math]")
{
  GIVEN("s=4.0")
  {
    jam::scalar s{ 4.F };// NOLINT It's OK to use magic numbers in unit tests.
    WHEN("I take the square root of s")
    {
      auto const result = sqrt(s);
      THEN("the result is 2")
      {
        REQUIRE(result == jam::scalar{ 2.F });// NOLINT It's OK to use magic numbers in unit tests.
      }
    }
  }
}