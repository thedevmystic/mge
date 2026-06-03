#include <catch2/catch_test_macros.hpp>

namespace mge::smoke::test {

TEST_CASE("Smoke Test", "[smoke][test]") {
  REQUIRE(1 == 1);
  REQUIRE(true == true);
  REQUIRE(1 + 1 == 2);
}

}  // namespace mge::smoke::test
