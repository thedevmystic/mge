/**
 * Copyright 2026-present Suryansh Singh (thedevmystic)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ------------------------------------------------------------------------------------------------
 *
 * @file core.test.cpp
 * @brief Consolidated verification tests for foundational metaprogramming primitives.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/core.hpp"

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

namespace {
  struct priority_low {};
  struct priority_high : priority_low {};

  struct SinaeDetector {
    template <typename T>
    auto check(priority_high) -> decltype(typename T::type(), std::true_type{}) { return {}; }
    template <typename T>
    auto check(priority_low) -> std::false_type { return {}; }
  };
}

TEST_CASE("mge::traits - Core Metaprogramming Verification", "[core][traits][core_traits]") {
  using namespace mge::traits;

  SECTION("conditional Verification") {
    STATIC_REQUIRE(std::is_same_v<typename conditional<true, int, float>::type, int>);
    STATIC_REQUIRE(std::is_same_v<typename conditional<true, int, float>::type, int>);
    STATIC_REQUIRE(std::is_same_v<conditional_t<true, int, float>, int>);
    STATIC_REQUIRE(std::is_same_v<conditional_t<false, int, float>, float>);
  }

  SECTION("enable_if Verification") {
    // True Path
    STATIC_REQUIRE(std::is_same_v<typename enable_if<true>::type, void>);
    STATIC_REQUIRE(std::is_same_v<typename enable_if<true, int>::type, int>);
    STATIC_REQUIRE(std::is_same_v<enable_if_t<true>, void>);
    STATIC_REQUIRE(std::is_same_v<enable_if_t<true, int>, int>);
    STATIC_REQUIRE(std::is_same_v<enable_if_t<true, float>, float>);
    // False Path
    SinaeDetector detector;
    STATIC_REQUIRE_FALSE(decltype(detector.check<enable_if<false>>(priority_high{}))::value);
    STATIC_REQUIRE_FALSE(decltype(detector.check<enable_if<false, int>>(priority_high{}))::value);
  }

  SECTION("integral_constant Verification") {
    using One = integral_constant<int, 1>;
    STATIC_REQUIRE(One::value == 1);
    STATIC_REQUIRE(One() == 1);
    STATIC_REQUIRE(static_cast<int>(One()) == 1);
    
    // bool_constant and aliases
    STATIC_REQUIRE(bool_constant<true>::value == true);
    STATIC_REQUIRE(true_type::value == true);
    STATIC_REQUIRE(false_type::value == false);
  }
}
