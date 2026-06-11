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
 * @file secondary_classification.test.cpp
 * @brief Consolidated verification tests for secondary classification type traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/secondary_classification.hpp"

#include <catch2/catch_test_macros.hpp>

namespace {
  struct DummyClass {};
  union DummyUnion {};
  enum DummyEnum { Value };
  enum class DummyEnumClass { Value };
}

TEST_CASE("mge::traits - Secondary Classification Verification", "[core][traits][secondary_classification]") {
  using namespace mge::traits;

  SECTION("is_reference Verification") {
    STATIC_REQUIRE(is_reference<int&>::value);
    STATIC_REQUIRE(is_reference_v<int&>);
    STATIC_REQUIRE(is_reference_v<int&&>);
    STATIC_REQUIRE(is_reference_v<const float&>);
    STATIC_REQUIRE(is_reference_v<const float&&>);
    STATIC_REQUIRE_FALSE(is_reference_v<int>);
    STATIC_REQUIRE_FALSE(is_reference_v<int*>);
  }

  SECTION("is_arithmetic Verification") {
    STATIC_REQUIRE(is_arithmetic<int>::value);
    STATIC_REQUIRE(is_arithmetic_v<bool>);
    STATIC_REQUIRE(is_arithmetic_v<char>);
    STATIC_REQUIRE(is_arithmetic_v<float>);
    STATIC_REQUIRE(is_arithmetic_v<double>);
    STATIC_REQUIRE(is_arithmetic_v<const unsigned long long>);
    STATIC_REQUIRE(is_arithmetic_v<volatile long double>);
    STATIC_REQUIRE_FALSE(is_arithmetic_v<void>);
    STATIC_REQUIRE_FALSE(is_arithmetic_v<int*>);
    STATIC_REQUIRE_FALSE(is_arithmetic_v<DummyClass>);
  }

  SECTION("is_fundamental Verification") {
    STATIC_REQUIRE(is_fundamental<void>::value);
    STATIC_REQUIRE(is_fundamental_v<int>);
    STATIC_REQUIRE(is_fundamental_v<float>);
    STATIC_REQUIRE(is_fundamental_v<bool>);
    STATIC_REQUIRE(is_fundamental_v<decltype(nullptr)>);
    STATIC_REQUIRE(is_fundamental_v<const double>);
    STATIC_REQUIRE_FALSE(is_fundamental_v<int*>);
    STATIC_REQUIRE_FALSE(is_fundamental_v<DummyClass>);
    STATIC_REQUIRE_FALSE(is_fundamental_v<DummyEnum>);
  }

  SECTION("is_member_pointer Verification") {
    STATIC_REQUIRE(is_member_pointer<int DummyClass::*>::value);
    STATIC_REQUIRE(is_member_pointer_v<int DummyClass::*>);
    STATIC_REQUIRE(is_member_pointer_v<void (DummyClass::*)()>);
    STATIC_REQUIRE(is_member_pointer_v<int (DummyClass::*)(double) const>);
    STATIC_REQUIRE(is_member_pointer_v<const float DummyClass::*>);
    STATIC_REQUIRE_FALSE(is_member_pointer_v<int*>);
    STATIC_REQUIRE_FALSE(is_member_pointer_v<int>);
  }

  SECTION("is_scoped_enum Verification") {
    STATIC_REQUIRE(is_scoped_enum<DummyEnumClass>::value);
    STATIC_REQUIRE(is_scoped_enum_v<DummyEnumClass>);
    STATIC_REQUIRE_FALSE(is_scoped_enum_v<DummyEnum>);
    STATIC_REQUIRE_FALSE(is_scoped_enum_v<int>);
    STATIC_REQUIRE_FALSE(is_scoped_enum_v<DummyClass>);
  }

  SECTION("is_scalar Verification") {
    STATIC_REQUIRE(is_scalar<int>::value);
    STATIC_REQUIRE(is_scalar_v<float>);
    STATIC_REQUIRE(is_scalar_v<int*>);
    STATIC_REQUIRE(is_scalar_v<decltype(nullptr)>);
    STATIC_REQUIRE(is_scalar_v<DummyEnum>);
    STATIC_REQUIRE(is_scalar_v<DummyEnumClass>);
    STATIC_REQUIRE(is_scalar_v<int DummyClass::*>);
    STATIC_REQUIRE(is_scalar_v<void (DummyClass::*)()>);
    STATIC_REQUIRE_FALSE(is_scalar_v<void>);
    STATIC_REQUIRE_FALSE(is_scalar_v<DummyClass>);
    STATIC_REQUIRE_FALSE(is_scalar_v<int&>);
  }

  SECTION("is_object Verification") {
    STATIC_REQUIRE(is_object<int>::value);
    STATIC_REQUIRE(is_object_v<float>);
    STATIC_REQUIRE(is_object_v<int*>);
    STATIC_REQUIRE(is_object_v<DummyClass>);
    STATIC_REQUIRE(is_object_v<DummyUnion>);
    STATIC_REQUIRE(is_object_v<int[5]>);
    STATIC_REQUIRE(is_object_v<DummyEnum>);
    STATIC_REQUIRE_FALSE(is_object_v<void>);
    STATIC_REQUIRE_FALSE(is_object_v<int&>);
    STATIC_REQUIRE_FALSE(is_object_v<int&&>);
    STATIC_REQUIRE_FALSE(is_object_v<void()>);
  }

  SECTION("is_compound Verification") {
    STATIC_REQUIRE(is_compound<int*>::value);
    STATIC_REQUIRE(is_compound_v<int&>);
    STATIC_REQUIRE(is_compound_v<int&&>);
    STATIC_REQUIRE(is_compound_v<int[5]>);
    STATIC_REQUIRE(is_compound_v<void()>);
    STATIC_REQUIRE(is_compound_v<DummyClass>);
    STATIC_REQUIRE(is_compound_v<DummyUnion>);
    STATIC_REQUIRE(is_compound_v<DummyEnum>);
    STATIC_REQUIRE(is_compound_v<int DummyClass::*>);
    STATIC_REQUIRE_FALSE(is_compound_v<int>);
    STATIC_REQUIRE_FALSE(is_compound_v<float>);
    STATIC_REQUIRE_FALSE(is_compound_v<void>);
    STATIC_REQUIRE_FALSE(is_compound_v<decltype(nullptr)>);
  }
}
