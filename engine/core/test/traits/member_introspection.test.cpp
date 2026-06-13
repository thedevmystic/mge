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
 * @file member_introspection.test.cpp
 * @brief Consolidated verification tests for member introspection type traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/member_introspection.hpp"

#include <catch2/catch_test_macros.hpp>

namespace {
struct EmptyStruct {};

struct StandardLayoutStruct {
  int x;
  double y;
};

struct TrivialStruct {
  int x;
};

struct NonTrivialStruct {
  NonTrivialStruct() {} // User-defined constructor makes it non-trivial
  ~NonTrivialStruct() {}
};

struct LiteralStruct {
  int x;
};

struct PolymorphicClass {
  virtual void foo() {}
  virtual ~PolymorphicClass() = default;
};

struct AbstractClass {
  virtual void pure_virtual() = 0;
  virtual ~AbstractClass() = default;
};

struct FinalClass final {};

struct AggregateStruct {
  int a;
  float b;
};
}

TEST_CASE("mge::traits - Member Introspection Verification", "[core][traits][member_introspection]") {
  using namespace mge::traits;

  SECTION("is_standard_layout Verification") {
    STATIC_REQUIRE(is_standard_layout<StandardLayoutStruct>::value);
    STATIC_REQUIRE(is_standard_layout_v<StandardLayoutStruct>);
    STATIC_REQUIRE(is_standard_layout_v<int>);
    STATIC_REQUIRE_FALSE(is_standard_layout_v<PolymorphicClass>);
  }

  SECTION("is_trivially_copyable Verification") {
    STATIC_REQUIRE(is_trivially_copyable<TrivialStruct>::value);
    STATIC_REQUIRE(is_trivially_copyable_v<TrivialStruct>);
    STATIC_REQUIRE(is_trivially_copyable_v<int>);
    STATIC_REQUIRE_FALSE(is_trivially_copyable_v<NonTrivialStruct>);
  }

  SECTION("is_literal_type Verification") {
    STATIC_REQUIRE(is_literal_type<int>::value);
    STATIC_REQUIRE(is_literal_type_v<int[5][10]>);
    STATIC_REQUIRE(is_literal_type_v<int&>);
    STATIC_REQUIRE(is_literal_type_v<LiteralStruct>);
    STATIC_REQUIRE_FALSE(is_literal_type_v<NonTrivialStruct>);
    STATIC_REQUIRE_FALSE(is_literal_type_v<PolymorphicClass>);
  }

  SECTION("is_pod Verification") {
    STATIC_REQUIRE(is_pod<TrivialStruct>::value);
    STATIC_REQUIRE(is_pod_v<TrivialStruct>);
    STATIC_REQUIRE(is_pod_v<int>);
    STATIC_REQUIRE_FALSE(is_pod_v<NonTrivialStruct>);
  }

  SECTION("is_trivial Verification") {
    STATIC_REQUIRE(is_trivial<TrivialStruct>::value);
    STATIC_REQUIRE(is_trivial_v<TrivialStruct>);
    STATIC_REQUIRE(is_trivial_v<int>);
    STATIC_REQUIRE_FALSE(is_trivial_v<NonTrivialStruct>);
  }

  SECTION("is_empty Verification") {
    STATIC_REQUIRE(is_empty<EmptyStruct>::value);
    STATIC_REQUIRE(is_empty_v<EmptyStruct>);
    STATIC_REQUIRE_FALSE(is_empty_v<StandardLayoutStruct>);
  }

  SECTION("is_polymorphic Verification") {
    STATIC_REQUIRE(is_polymorphic<PolymorphicClass>::value);
    STATIC_REQUIRE(is_polymorphic_v<PolymorphicClass>);
    STATIC_REQUIRE(is_polymorphic_v<AbstractClass>);
    STATIC_REQUIRE_FALSE(is_polymorphic_v<StandardLayoutStruct>);
  }

  SECTION("is_abstract Verification") {
    STATIC_REQUIRE(is_abstract<AbstractClass>::value);
    STATIC_REQUIRE(is_abstract_v<AbstractClass>);
    STATIC_REQUIRE_FALSE(is_abstract_v<PolymorphicClass>);
  }

  SECTION("is_final Verification") {
    STATIC_REQUIRE(is_final<FinalClass>::value);
    STATIC_REQUIRE(is_final_v<FinalClass>);
    STATIC_REQUIRE_FALSE(is_final_v<EmptyStruct>);
  }

  SECTION("is_aggregate Verification") {
    STATIC_REQUIRE(is_aggregate<AggregateStruct>::value);
    STATIC_REQUIRE(is_aggregate_v<AggregateStruct>);
    STATIC_REQUIRE_FALSE(is_aggregate_v<NonTrivialStruct>);
  }
}
