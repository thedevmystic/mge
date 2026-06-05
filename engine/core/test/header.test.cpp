#include "header.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Dummy Test Case, [dummy]") {
  int val = func(1);
  int expected = 69;
  REQUIRE(val == expected);
  val = func(2);
  expected = 0;
  REQUIRE(val == expected);
}
