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
 * @file is_trivially_copyable.test.cpp
 * @brief Tests if `IsTriviallyCopyable` checks for trivially copyable structures.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/is_trivially_copyable.hpp"

#include <catch2/catch_test_macros.hpp>

namespace {
struct TrivialStruct {
  int a;
  float b;
};

struct NonTrivialStruct {
  NonTrivialStruct(const NonTrivialStruct&) {} // Custom copy constructor triggers non-trivial
};
} // namespace

TEST_CASE("mge::traits - IsTriviallyCopyable Verification", "[core][traits][is_trivially_copyable]") {
  using namespace mge::traits;

  SECTION("Trivially Copyable Types") {
    STATIC_REQUIRE(IsTriviallyCopyable<int>::Value);
    STATIC_REQUIRE(IsTriviallyCopyableV<int>);
    STATIC_REQUIRE(IsTriviallyCopyableV<double>);
    STATIC_REQUIRE(IsTriviallyCopyableV<TrivialStruct>);
  }

  SECTION("Non-Trivially Copyable Types") {
    STATIC_REQUIRE_FALSE(IsTriviallyCopyable<NonTrivialStruct>::Value);
    STATIC_REQUIRE_FALSE(IsTriviallyCopyableV<NonTrivialStruct>);
  }
}
