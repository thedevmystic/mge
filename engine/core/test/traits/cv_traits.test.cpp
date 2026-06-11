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
 * @file cv_traits.test.cpp
 * @brief Consolidated verification tests for CV-qualifier type traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/cv_traits.hpp"

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

namespace {
  struct DummyClass {};
}

TEST_CASE("mge::traits - CV-Qualifier Verification", "[core][traits][cv_traits]") {
  using namespace mge::traits;

  SECTION("is_const Verification") {
    STATIC_REQUIRE(is_const<const int>::value);
    STATIC_REQUIRE(is_const_v<const int>);
    STATIC_REQUIRE(is_const_v<const volatile int>);
    STATIC_REQUIRE(is_const_v<const float>);
    STATIC_REQUIRE(is_const_v<const DummyClass>);
    STATIC_REQUIRE_FALSE(is_const_v<int>);
    STATIC_REQUIRE_FALSE(is_const_v<volatile int>);
    STATIC_REQUIRE_FALSE(is_const_v<int*>);         // pointer itself is not const
    STATIC_REQUIRE(is_const_v<int* const>);         // but this one is
  }

  SECTION("is_volatile Verification") {
    STATIC_REQUIRE(is_volatile<volatile int>::value);
    STATIC_REQUIRE(is_volatile_v<volatile int>);
    STATIC_REQUIRE(is_volatile_v<const volatile int>);
    STATIC_REQUIRE(is_volatile_v<volatile float>);
    STATIC_REQUIRE(is_volatile_v<volatile DummyClass>);
    STATIC_REQUIRE_FALSE(is_volatile_v<int>);
    STATIC_REQUIRE_FALSE(is_volatile_v<const int>);
    STATIC_REQUIRE_FALSE(is_volatile_v<int*>);      // pointer itself is not volatile
    STATIC_REQUIRE(is_volatile_v<int* volatile>);   // but this one is
  }

  SECTION("is_cv Verification") {
    STATIC_REQUIRE(is_cv<const int>::value);
    STATIC_REQUIRE(is_cv_v<volatile int>);
    STATIC_REQUIRE(is_cv_v<const volatile int>);
    STATIC_REQUIRE(is_cv_v<const DummyClass>);
    STATIC_REQUIRE(is_cv_v<volatile DummyClass>);
    STATIC_REQUIRE_FALSE(is_cv_v<int>);
    STATIC_REQUIRE_FALSE(is_cv_v<float>);
    STATIC_REQUIRE_FALSE(is_cv_v<DummyClass>);
  }

  SECTION("add_const Verification") {
    STATIC_REQUIRE(std::is_same_v<add_const_t<int>, const int>);
    STATIC_REQUIRE(std::is_same_v<add_const_t<float>, const float>);
    STATIC_REQUIRE(std::is_same_v<add_const_t<DummyClass>, const DummyClass>);
    // Already const — idempotent
    STATIC_REQUIRE(std::is_same_v<add_const_t<const int>, const int>);
    // References and functions must not be modified
    STATIC_REQUIRE(std::is_same_v<add_const_t<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<add_const_t<int&&>, int&&>);
    STATIC_REQUIRE(std::is_same_v<add_const_t<void()>, void()>);
  }

  SECTION("add_volatile Verification") {
    STATIC_REQUIRE(std::is_same_v<add_volatile_t<int>, volatile int>);
    STATIC_REQUIRE(std::is_same_v<add_volatile_t<float>, volatile float>);
    STATIC_REQUIRE(std::is_same_v<add_volatile_t<DummyClass>, volatile DummyClass>);
    // Already volatile — idempotent
    STATIC_REQUIRE(std::is_same_v<add_volatile_t<volatile int>, volatile int>);
    // References and functions must not be modified
    STATIC_REQUIRE(std::is_same_v<add_volatile_t<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<add_volatile_t<int&&>, int&&>);
    STATIC_REQUIRE(std::is_same_v<add_volatile_t<void()>, void()>);
  }

  SECTION("add_cv Verification") {
    STATIC_REQUIRE(std::is_same_v<add_cv_t<int>, const volatile int>);
    STATIC_REQUIRE(std::is_same_v<add_cv_t<float>, const volatile float>);
    STATIC_REQUIRE(std::is_same_v<add_cv_t<DummyClass>, const volatile DummyClass>);
    // Already fully qualified — idempotent
    STATIC_REQUIRE(std::is_same_v<add_cv_t<const volatile int>, const volatile int>);
    // Partial qualification is completed
    STATIC_REQUIRE(std::is_same_v<add_cv_t<const int>, const volatile int>);
    STATIC_REQUIRE(std::is_same_v<add_cv_t<volatile int>, const volatile int>);
    // References and functions must not be modified
    STATIC_REQUIRE(std::is_same_v<add_cv_t<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<add_cv_t<void()>, void()>);
  }

  SECTION("remove_const Verification") {
    STATIC_REQUIRE(std::is_same_v<remove_const_t<const int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_const_t<const float>, float>);
    STATIC_REQUIRE(std::is_same_v<remove_const_t<const DummyClass>, DummyClass>);
    // volatile is preserved
    STATIC_REQUIRE(std::is_same_v<remove_const_t<const volatile int>, volatile int>);
    // Non-const types are unchanged
    STATIC_REQUIRE(std::is_same_v<remove_const_t<int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_const_t<volatile int>, volatile int>);
  }

  SECTION("remove_volatile Verification") {
    STATIC_REQUIRE(std::is_same_v<remove_volatile_t<volatile int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_volatile_t<volatile float>, float>);
    STATIC_REQUIRE(std::is_same_v<remove_volatile_t<volatile DummyClass>, DummyClass>);
    // const is preserved
    STATIC_REQUIRE(std::is_same_v<remove_volatile_t<const volatile int>, const int>);
    // Non-volatile types are unchanged
    STATIC_REQUIRE(std::is_same_v<remove_volatile_t<int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_volatile_t<const int>, const int>);
  }

  SECTION("remove_cv Verification") {
    STATIC_REQUIRE(std::is_same_v<remove_cv_t<const int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_cv_t<volatile int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_cv_t<const volatile int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_cv_t<const float>, float>);
    STATIC_REQUIRE(std::is_same_v<remove_cv_t<volatile DummyClass>, DummyClass>);
    STATIC_REQUIRE(std::is_same_v<remove_cv_t<const volatile DummyClass>, DummyClass>);
    // Unqualified types are unchanged
    STATIC_REQUIRE(std::is_same_v<remove_cv_t<int>, int>);
    STATIC_REQUIRE(std::is_same_v<remove_cv_t<DummyClass>, DummyClass>);
  }
}
