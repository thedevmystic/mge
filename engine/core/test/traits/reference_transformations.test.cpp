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
 * @file reference_transformations.test.cpp
 * @brief Consolidated verification tests for reference transformation traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/reference_transformations.hpp"

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

TEST_CASE("mge::traits - Reference Transformations Verification", "[core][traits][reference_transformations]") {
  using namespace mge::traits;

  SECTION("add_lvalue_reference Verification") {
    // Plain types
    STATIC_REQUIRE(std::is_same_v<typename add_lvalue_reference<int>::type, int&>);
    STATIC_REQUIRE(std::is_same_v<add_lvalue_reference_t<float>, float&>);

    // Reference types
    STATIC_REQUIRE(std::is_same_v<add_lvalue_reference_t<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<add_lvalue_reference_t<int&&>, int&>);

    // Qualified and Pointer types
    STATIC_REQUIRE(std::is_same_v<add_lvalue_reference_t<const double>, const double&>);
    STATIC_REQUIRE(std::is_same_v<add_lvalue_reference_t<int*>, int*&>);
  }

  SECTION("add_rvalue_reference Verification") {
    // Plain types
    STATIC_REQUIRE(std::is_same_v<typename add_rvalue_reference<int>::type, int&&>);
    STATIC_REQUIRE(std::is_same_v<add_rvalue_reference_t<float>, float&&>);

    // Reference types
    STATIC_REQUIRE(std::is_same_v<add_rvalue_reference_t<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<add_rvalue_reference_t<int&&>, int&&>);

    // Qualified and Pointer types
    STATIC_REQUIRE(std::is_same_v<add_rvalue_reference_t<const double>, const double&&>);
    STATIC_REQUIRE(std::is_same_v<add_rvalue_reference_t<int*>, int*&&>);
  }

  SECTION("remove_reference Verification") {
    // Non-Reference types
    STATIC_REQUIRE(std::is_same_v<typename remove_reference<int>::type, int>);
    STATIC_REQUIRE(std::is_same_v<remove_reference_t<int*>, int*>);

    // Reference types
    STATIC_REQUIRE(std::is_same_v<typename remove_reference<int&>::type, int>);
    STATIC_REQUIRE(std::is_same_v<remove_reference_t<const int&>, const int>);

    // Rvalue Reference
    STATIC_REQUIRE(std::is_same_v<typename remove_reference<int&&>::type, int>);
    STATIC_REQUIRE(std::is_same_v<remove_reference_t<volatile int&&>, volatile int>);
  }

  SECTION("remove_cvref Verification") {
    // Plain types
    STATIC_REQUIRE(std::is_same_v<typename remove_cvref<int>::type, int>);
    STATIC_REQUIRE(std::is_same_v<remove_cvref_t<float>, float>);

    // Mixed Reference and CV Qualifiers
    STATIC_REQUIRE(std::is_same_v<typename remove_cvref<const int&>::type, int>);
    STATIC_REQUIRE(std::is_same_v<remove_cvref_t<volatile int&&>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_cvref_t<const volatile double&>, double>);

    // Pointers with Reference Wrappers
    STATIC_REQUIRE(std::is_same_v<remove_cvref_t<const int* const&>, const int*>);
  }
}
