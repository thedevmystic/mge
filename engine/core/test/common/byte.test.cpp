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
 * @file byte.test.cpp
 * @brief Tests mge::Byte implementation.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "common/byte.hpp"

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

#include "common/types.hpp"

TEST_CASE("mge::types - Byte Underlying Properties", "[core][types][byte]") {
  using namespace mge::types;

  SECTION("Size and Type Characteristics") {
    // A byte must be exactly 1 byte (8 bits)
    STATIC_REQUIRE(sizeof(Byte) == 1);

    // It should behave as an enum class, not a standard integral type directly
    STATIC_REQUIRE(std::is_enum_v<Byte>);
    STATIC_REQUIRE_FALSE(std::is_integral_v<Byte>);

    // Ensure the underlying type is strictly an uint8
    STATIC_REQUIRE(std::is_same_v<std::underlying_type_t<Byte>, uint8>);
  }
}

TEST_CASE("mge::types - Byte Bitwise Operations", "[core][types][byte]") {
  using namespace mge::types;

  // Helper values for testing bit manipulations
  constexpr Byte b_zero{0x00};
  constexpr Byte b_all{0xFF};
  constexpr Byte b_alt1{0xAA};  // 10101010
  constexpr Byte b_alt2{0x55};  // 01010101

  SECTION("Bitwise AND (&)") {
    STATIC_REQUIRE((b_alt1 & b_alt2) == b_zero);
    STATIC_REQUIRE((b_alt1 & b_all) == b_alt1);
  }

  SECTION("Bitwise OR (|)") {
    STATIC_REQUIRE((b_alt1 | b_alt2) == b_all);
    STATIC_REQUIRE((b_alt1 | b_zero) == b_alt1);
  }

  SECTION("Bitwise XOR (^)") {
    STATIC_REQUIRE((b_alt1 ^ b_alt2) == b_all);
    STATIC_REQUIRE((b_alt1 ^ b_alt1) == b_zero);
  }

  SECTION("Bitwise NOT (~)") {
    STATIC_REQUIRE(~b_zero == b_all);
    STATIC_REQUIRE(~b_alt1 == b_alt2);
  }

  SECTION("Bitwise Shifting (<<, >>)") {
    constexpr Byte b_bit1{0x01};
    constexpr Byte b_bit2{0x02};
    constexpr Byte b_high{0x80};

    STATIC_REQUIRE((b_bit1 << 1) == b_bit2);
    STATIC_REQUIRE((b_high >> 7) == b_bit1);
    STATIC_REQUIRE((b_high << 1) == b_zero);  // Verifies overflow drops bits
  }
}

TEST_CASE("mge::types - Byte Compound Assignment Operations", "[core][types][byte]") {
  using namespace mge::types;

  SECTION("Compound Assignment Modifiers") {
    Byte b{0xAA};

    // Test &=
    b &= Byte{0xF0};
    REQUIRE(b == Byte{0xA0});

    // Test |=
    b |= Byte{0x05};
    REQUIRE(b == Byte{0xA5});

    // Test ^=
    b ^= Byte{0xA5};
    REQUIRE(b == Byte{0x00});

    // Reset for shift testing
    b = Byte{0x01};

    // Test <<=
    b <<= 4;
    REQUIRE(b == Byte{0x10});

    // Test >>=
    b >>= 3;
    REQUIRE(b == Byte{0x02});
  }
}
