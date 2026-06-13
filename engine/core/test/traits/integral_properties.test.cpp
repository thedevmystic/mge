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
 * @file integral_properties.test.cpp
 * @brief Consolidated verification tests for integral property query and transformation type traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/integral_properties.hpp"

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

namespace {
  struct DummyClass {};
}

TEST_CASE("mge::traits - Integral Property Verification", "[core][traits][integral_properties]") {
  using namespace mge::traits;

  SECTION("is_signed Verification") {
    STATIC_REQUIRE(is_signed<int>::value);
    STATIC_REQUIRE(is_signed_v<int>);
    STATIC_REQUIRE(is_signed_v<signed char>);
    STATIC_REQUIRE(is_signed_v<long long>);
    STATIC_REQUIRE(is_signed_v<const int>);
    STATIC_REQUIRE(is_signed_v<volatile double>);

    // Non-arithmetic or unsigned types
    STATIC_REQUIRE_FALSE(is_signed_v<unsigned int>);
    STATIC_REQUIRE_FALSE(is_signed_v<unsigned char>);
    STATIC_REQUIRE_FALSE(is_signed_v<DummyClass>);
    STATIC_REQUIRE_FALSE(is_signed_v<int*>);
  }

  SECTION("is_unsigned Verification") {
    STATIC_REQUIRE(is_unsigned<unsigned int>::value);
    STATIC_REQUIRE(is_unsigned_v<unsigned int>);
    STATIC_REQUIRE(is_unsigned_v<unsigned char>);
    STATIC_REQUIRE(is_unsigned_v<const unsigned long long>);

    // Floating points are never unsigned traits-wise, signed types are false
    STATIC_REQUIRE_FALSE(is_unsigned_v<int>);
    STATIC_REQUIRE_FALSE(is_unsigned_v<double>);
    STATIC_REQUIRE_FALSE(is_unsigned_v<DummyClass>);
    STATIC_REQUIRE_FALSE(is_unsigned_v<unsigned int*>);
  }

  SECTION("make_signed Verification") {
    STATIC_REQUIRE(std::is_same_v<make_signed_t<unsigned int>, int>);
    STATIC_REQUIRE(std::is_same_v<make_signed_t<unsigned char>, signed char>);
    STATIC_REQUIRE(std::is_same_v<make_signed_t<char>, signed char>);
    STATIC_REQUIRE(std::is_same_v<make_signed_t<wchar_t>, int>);
    STATIC_REQUIRE(std::is_same_v<make_signed_t<char16_t>, short>);
    STATIC_REQUIRE(std::is_same_v<make_signed_t<char32_t>, int>);

    // Already signed — pass through
    STATIC_REQUIRE(std::is_same_v<make_signed_t<int>, int>);

    // CV-preservation
    STATIC_REQUIRE(std::is_same_v<make_signed_t<const unsigned int>, const int>);
    STATIC_REQUIRE(std::is_same_v<make_signed_t<volatile unsigned char>, volatile signed char>);
    STATIC_REQUIRE(std::is_same_v<make_signed_t<const volatile unsigned long>, const volatile long>);
  }

  SECTION("make_unsigned Verification") {
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<int>, unsigned int>);
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<signed char>, unsigned char>);
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<char>, unsigned char>);
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<wchar_t>, unsigned int>);
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<char16_t>, unsigned short>);
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<char32_t>, unsigned int>);

    // Already unsigned — pass through
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<unsigned int>, unsigned int>);

    // CV-preservation
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<const int>, const unsigned int>);
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<volatile signed char>, volatile unsigned char>);
    STATIC_REQUIRE(std::is_same_v<make_unsigned_t<const volatile long>, const volatile unsigned long>);
  }
}
