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
 * @file primary_classification.test.cpp
 * @brief Consolidated verification tests for primary classification type traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/primary_classification.hpp"

#include <catch2/catch_test_macros.hpp>

namespace {
  struct DummyClass {};
  union DummyUnion {};
  enum DummyEnum { Value };
  enum class DummyEnumClass { Value };
}

TEST_CASE("mge::traits - Primary Classification Verification", "[core][traits][primary_classification]") {
  using namespace mge::traits;

  SECTION("is_void Verification") {
    STATIC_REQUIRE(is_void<void>::value);
    STATIC_REQUIRE(is_void_v<void>);
    STATIC_REQUIRE(is_void_v<const void>);
    STATIC_REQUIRE(is_void_v<volatile void>);
    STATIC_REQUIRE(is_void_v<const volatile void>);
    STATIC_REQUIRE_FALSE(is_void_v<int>);
  }

  SECTION("is_null_pointer Verification") {
    STATIC_REQUIRE(is_null_pointer<decltype(nullptr)>::value);
    STATIC_REQUIRE(is_null_pointer_v<decltype(nullptr)>);
    STATIC_REQUIRE(is_null_pointer_v<const decltype(nullptr)>);
    STATIC_REQUIRE_FALSE(is_null_pointer_v<int*>);
  }

  SECTION("is_integral Verification") {
    STATIC_REQUIRE(is_integral<int>::value);
    STATIC_REQUIRE(is_integral_v<bool>);
    STATIC_REQUIRE(is_integral_v<char>);
    STATIC_REQUIRE(is_integral_v<const unsigned long long>);
    STATIC_REQUIRE_FALSE(is_integral_v<float>);
    STATIC_REQUIRE_FALSE(is_integral_v<DummyClass>);
  }

  SECTION("is_floating_point Verification") {
    STATIC_REQUIRE(is_floating_point<float>::value);
    STATIC_REQUIRE(is_floating_point_v<double>);
    STATIC_REQUIRE(is_floating_point_v<const long double>);
    STATIC_REQUIRE_FALSE(is_floating_point_v<int>);
  }

  SECTION("is_array Verification") {
    STATIC_REQUIRE(is_array<int[]>::value);
    STATIC_REQUIRE(is_array_v<int[5]>);
    STATIC_REQUIRE(is_array_v<const float[2][3]>);
    STATIC_REQUIRE_FALSE(is_array_v<int*>);
  }

  SECTION("is_pointer Verification") {
    STATIC_REQUIRE(is_pointer<int*>::value);
    STATIC_REQUIRE(is_pointer_v<const float*>);
    STATIC_REQUIRE(is_pointer_v<void*>);
    STATIC_REQUIRE_FALSE(is_pointer_v<int>);
    STATIC_REQUIRE_FALSE(is_pointer_v<int&>);
  }

  SECTION("is_lvalue_reference Verification") {
    STATIC_REQUIRE(is_lvalue_reference<int&>::value);
    STATIC_REQUIRE(is_lvalue_reference_v<const float&>);
    STATIC_REQUIRE_FALSE(is_lvalue_reference_v<int&&>);
    STATIC_REQUIRE_FALSE(is_lvalue_reference_v<int>);
  }

  SECTION("is_rvalue_reference Verification") {
    STATIC_REQUIRE(is_rvalue_reference<int&&>::value);
    STATIC_REQUIRE(is_rvalue_reference_v<const float&&>);
    STATIC_REQUIRE_FALSE(is_rvalue_reference_v<int&>);
    STATIC_REQUIRE_FALSE(is_rvalue_reference_v<int>);
  }

  SECTION("is_enum Verification") {
    STATIC_REQUIRE(is_enum<DummyEnum>::value);
    STATIC_REQUIRE(is_enum_v<DummyEnumClass>);
    STATIC_REQUIRE_FALSE(is_enum_v<int>);
  }

  SECTION("is_class Verification") {
    STATIC_REQUIRE(is_class<DummyClass>::value);
    STATIC_REQUIRE_FALSE(is_class_v<DummyUnion>);
    STATIC_REQUIRE_FALSE(is_class_v<int>);
  }

  SECTION("is_union Verification") {
    STATIC_REQUIRE(is_union<DummyUnion>::value);
    STATIC_REQUIRE_FALSE(is_union_v<DummyClass>);
    STATIC_REQUIRE_FALSE(is_union_v<int>);
  }

  SECTION("is_function Verification") {
    STATIC_REQUIRE(is_function<void()>::value);
    STATIC_REQUIRE(is_function_v<int(double)>);
    STATIC_REQUIRE_FALSE(is_function_v<void(*)()>);
    STATIC_REQUIRE_FALSE(is_function_v<int>);
  }

  SECTION("is_member_function_pointer Verification") {
    STATIC_REQUIRE(is_member_function_pointer<void (DummyClass::*)()>::value);
    STATIC_REQUIRE(is_member_function_pointer_v<int (DummyClass::*)(double) const>);
    STATIC_REQUIRE(is_member_function_pointer_v<void (DummyClass::*)() volatile>);
    STATIC_REQUIRE_FALSE(is_member_function_pointer_v<void(*)()>);
    STATIC_REQUIRE_FALSE(is_member_function_pointer_v<int DummyClass::*>);
  }

  SECTION("is_member_object_pointer Verification") {
    STATIC_REQUIRE(is_member_object_pointer<int DummyClass::*>::value);
    STATIC_REQUIRE(is_member_object_pointer_v<const float DummyClass::*>);
    STATIC_REQUIRE(is_member_object_pointer_v<DummyUnion DummyClass::* volatile>);
    STATIC_REQUIRE_FALSE(is_member_object_pointer_v<int*>);
    STATIC_REQUIRE_FALSE(is_member_object_pointer_v<void (DummyClass::*)()>);
  }
}
