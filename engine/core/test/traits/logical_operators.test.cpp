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
 * @file logical_operators.test.cpp
 * @brief Consolidated verification tests for compile-time logical operator type traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/logical_operators.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("mge::traits - Logical Operators Verification", "[core][traits][logical_operators]") {
  using namespace mge::traits;

  SECTION("conjunction Verification") {
    // Empty conjunction base case
    STATIC_REQUIRE(conjunction<>::value);
    STATIC_REQUIRE(conjunction_v<>);

    // Single trait verification
    STATIC_REQUIRE(conjunction<true_type>::value);
    STATIC_REQUIRE_FALSE(conjunction<false_type>::value);

    // Multiple traits verification
    STATIC_REQUIRE(conjunction<true_type, true_type>::value);
    STATIC_REQUIRE_FALSE(conjunction<true_type, false_type>::value);
    STATIC_REQUIRE_FALSE(conjunction<false_type, true_type>::value);
    STATIC_REQUIRE_FALSE(conjunction<false_type, false_type>::value);

    // Multi-argument and short-circuit verification
    STATIC_REQUIRE(conjunction<true_type, true_type, true_type>::value);
    STATIC_REQUIRE_FALSE(conjunction<true_type, false_type, true_type>::value);

    // Variable template verification
    STATIC_REQUIRE(conjunction_v<true_type>);
    STATIC_REQUIRE_FALSE(conjunction_v<false_type>);
    STATIC_REQUIRE(conjunction_v<true_type, true_type>);
    STATIC_REQUIRE_FALSE(conjunction_v<true_type, false_type>);
  }

  SECTION("disjunction Verification") {
    // Empty disjunction base case
    STATIC_REQUIRE_FALSE(disjunction<>::value);
    STATIC_REQUIRE_FALSE(disjunction_v<>);

    // Single trait verification
    STATIC_REQUIRE(disjunction<true_type>::value);
    STATIC_REQUIRE_FALSE(disjunction<false_type>::value);

    // Multiple traits verification
    STATIC_REQUIRE(disjunction<true_type, true_type>::value);
    STATIC_REQUIRE(disjunction<true_type, false_type>::value);
    STATIC_REQUIRE(disjunction<false_type, true_type>::value);
    STATIC_REQUIRE_FALSE(disjunction<false_type, false_type>::value);

    // Multi-argument verification
    STATIC_REQUIRE(disjunction<false_type, false_type, true_type>::value);
    STATIC_REQUIRE_FALSE(disjunction<false_type, false_type, false_type>::value);

    // Variable template verification
    STATIC_REQUIRE(disjunction_v<true_type>);
    STATIC_REQUIRE_FALSE(disjunction_v<false_type>);
    STATIC_REQUIRE(disjunction_v<false_type, true_type>);
    STATIC_REQUIRE_FALSE(disjunction_v<false_type, false_type>);
  }

  SECTION("negation Verification") {
    // Trait verification
    STATIC_REQUIRE_FALSE(negation<true_type>::value);
    STATIC_REQUIRE(negation<false_type>::value);

    // Variable template verification
    STATIC_REQUIRE_FALSE(negation_v<true_type>);
    STATIC_REQUIRE(negation_v<false_type>);
  }
}
