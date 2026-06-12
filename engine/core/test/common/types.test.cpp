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
 * @file types.test.cpp
 * @brief Tests if types are correctly setup.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "common/types.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdint>
#include <type_traits>

TEST_CASE("mge::types - Fixed-width Integer Size and Signedness Verification",
          "[core][types][integers]") {
  using namespace mge::types;

  SECTION("Signed Integers") {
    STATIC_REQUIRE(sizeof(int8) == 1);
    STATIC_REQUIRE(std::is_signed_v<int8>);

    STATIC_REQUIRE(sizeof(int16) == 2);
    STATIC_REQUIRE(std::is_signed_v<int16>);

    STATIC_REQUIRE(sizeof(int32) == 4);
    STATIC_REQUIRE(std::is_signed_v<int32>);

    STATIC_REQUIRE(sizeof(int64) == 8);
    STATIC_REQUIRE(std::is_signed_v<int64>);
  }

  SECTION("Unsigned Integers") {
    STATIC_REQUIRE(sizeof(uint8) == 1);
    STATIC_REQUIRE(std::is_unsigned_v<uint8>);

    STATIC_REQUIRE(sizeof(uint16) == 2);
    STATIC_REQUIRE(std::is_unsigned_v<uint16>);

    STATIC_REQUIRE(sizeof(uint32) == 4);
    STATIC_REQUIRE(std::is_unsigned_v<uint32>);

    STATIC_REQUIRE(sizeof(uint64) == 8);
    STATIC_REQUIRE(std::is_unsigned_v<uint64>);
  }
}

TEST_CASE("mge::types - Pointer and Size Types Verification", "[core][types][pointer]") {
  using namespace mge::types;

  SECTION("Pointer-sized Integers") {
    STATIC_REQUIRE(sizeof(intptr) == sizeof(void*));
    STATIC_REQUIRE(std::is_signed_v<intptr>);

    STATIC_REQUIRE(sizeof(uintptr) == sizeof(void*));
    STATIC_REQUIRE(std::is_unsigned_v<uintptr>);
  }

  SECTION("Size and Pointer Difference Types") {
    STATIC_REQUIRE(sizeof(size_t) == sizeof(std::size_t));
    STATIC_REQUIRE(std::is_unsigned_v<size_t>);

    STATIC_REQUIRE(sizeof(ptrdiff) == sizeof(std::ptrdiff_t));
    STATIC_REQUIRE(std::is_signed_v<ptrdiff>);
  }
}

TEST_CASE("mge::types - Special Types and Constants", "[core][types][constants]") {
  using namespace mge::types;

  SECTION("Null Type") {
    // Verifies null_type is a valid type alias and matches std::nullptr_t behavior
    STATIC_REQUIRE(std::is_same_v<null_type, std::nullptr_t>);
  }

  SECTION("Exit Codes") {
    // Verify type and value of constants at compile-time
    STATIC_REQUIRE(std::is_same_v<decltype(EXIT_CODE_SUCCESS), const int8>);
    STATIC_REQUIRE(EXIT_CODE_SUCCESS == 0);

    STATIC_REQUIRE(std::is_same_v<decltype(EXIT_CODE_FAILURE), const int8>);
    STATIC_REQUIRE(EXIT_CODE_FAILURE == 1);
  }
}
