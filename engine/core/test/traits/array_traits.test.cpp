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
 * @file array_traits.test.cpp
 * @brief Consolidated verification tests for Array type traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/array_traits.hpp"

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

namespace {
  struct DummyClass {};
}

TEST_CASE("mge::traits - Array Verification", "[core][traits][array_traits]") {
  using namespace mge::traits;

  SECTION("rank Verification") {
    STATIC_REQUIRE(rank<int>::value == 0);
    STATIC_REQUIRE(rank_v<int> == 0);
    STATIC_REQUIRE(rank_v<DummyClass> == 0);
    
    // 1D Arrays
    STATIC_REQUIRE(rank_v<int[]> == 1);
    STATIC_REQUIRE(rank_v<int[42]> == 1);
    
    // Multi-dimensional Arrays
    STATIC_REQUIRE(rank_v<int[][100]> == 2);
    STATIC_REQUIRE(rank_v<int[8][16]> == 2);
    STATIC_REQUIRE(rank_v<int[3][5][7][9]> == 4);
  }

  SECTION("extent Verification") {
    STATIC_REQUIRE(extent<int>::value == 0);
    STATIC_REQUIRE(extent_v<int> == 0);
    
    // Unbounded fallback/dimension checks
    STATIC_REQUIRE(extent_v<int[]> == 0);
    STATIC_REQUIRE(extent_v<int[][256]> == 0);
    
    // Bounded dimension checks
    STATIC_REQUIRE(extent_v<int[64]> == 64);
    STATIC_REQUIRE(extent_v<int[1024][512]> == 1024);
    STATIC_REQUIRE(extent_v<int[7][11][13]> == 7);
  }

  SECTION("is_unbounded_array Verification") {
    STATIC_REQUIRE(is_unbounded_array<int[]>::value);
    STATIC_REQUIRE(is_unbounded_array_v<int[]>);
    STATIC_REQUIRE(is_unbounded_array_v<const int[]>);
    STATIC_REQUIRE(is_unbounded_array_v<int[][4096]>);
    
    STATIC_REQUIRE_FALSE(is_unbounded_array_v<int>);
    STATIC_REQUIRE_FALSE(is_unbounded_array_v<int[128]>);
    STATIC_REQUIRE_FALSE(is_unbounded_array_v<int[16][32]>);
    STATIC_REQUIRE_FALSE(is_unbounded_array_v<int*>);
  }

  SECTION("is_bounded_array Verification") {
    STATIC_REQUIRE(is_bounded_array<int[512]>::value);
    STATIC_REQUIRE(is_bounded_array_v<int[12]>);
    STATIC_REQUIRE(is_bounded_array_v<const int[99]>);
    STATIC_REQUIRE(is_bounded_array_v<int[4][20]>);
    
    STATIC_REQUIRE_FALSE(is_bounded_array_v<int>);
    STATIC_REQUIRE_FALSE(is_bounded_array_v<int[]>);
    STATIC_REQUIRE_FALSE(is_bounded_array_v<int[][12]>);
    STATIC_REQUIRE_FALSE(is_bounded_array_v<int*>);
  }

  SECTION("remove_extent Verification") {
    STATIC_REQUIRE(std::is_same_v<remove_extent_t<int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_extent_t<DummyClass>, DummyClass>);
    STATIC_REQUIRE(std::is_same_v<remove_extent_t<int[]>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_extent_t<int[24]>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_extent_t<int[][36]>, int[36]>);
    STATIC_REQUIRE(std::is_same_v<remove_extent_t<int[8][64]>, int[64]>);
    STATIC_REQUIRE(std::is_same_v<remove_extent_t<const int[128]>, const int>);
  }

  SECTION("remove_all_extents Verification") {
    STATIC_REQUIRE(std::is_same_v<remove_all_extents_t<int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_all_extents_t<DummyClass>, DummyClass>);
    STATIC_REQUIRE(std::is_same_v<remove_all_extents_t<int[]>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_all_extents_t<int[48]>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_all_extents_t<int[][72]>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_all_extents_t<int[14][28]>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_all_extents_t<int[2][4][8][16]>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_all_extents_t<const int[10][20]>, const int>);
  }
}
