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
 * @file pointer_transformations.test.cpp
 * @brief Consolidated verification tests for pointer transformation traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/pointer_transformations.hpp"

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

TEST_CASE("mge::traits - Pointer Transformations Verification", "[core][traits][pointer_transformations]") {
  using namespace mge::traits;

  SECTION("remove_pointer Verification") {
    // Non-Pointer types
    STATIC_REQUIRE(std::is_same_v<typename remove_pointer<int>::type, int>);
    STATIC_REQUIRE(std::is_same_v<remove_pointer_t<const float>, const float>);
    STATIC_REQUIRE(std::is_same_v<typename remove_pointer<int&>::type, int&>);
    STATIC_REQUIRE(std::is_same_v<remove_pointer_t<float&&>, float&&>);

    // Pointer types
    STATIC_REQUIRE(std::is_same_v<typename remove_pointer<int*>::type, int>);
    STATIC_REQUIRE(std::is_same_v<remove_pointer_t<int* const>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_pointer_t<volatile int* const>, volatile int>);
  }
}
