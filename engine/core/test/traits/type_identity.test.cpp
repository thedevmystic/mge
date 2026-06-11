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
 * @file type_identity.test.cpp
 * @brief Consolidated verification tests for type equivalence and classification traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/type_identity.hpp"
#include "common/types.hpp" 

#include <catch2/catch_test_macros.hpp>

namespace {
// Dummy structs
struct A {};
struct B {};
// Dummy Function
void func() {}
// Dummy Union
union U { int i; float f; };
}

TEST_CASE("mge::traits - Type Identity Verification", "[core][traits][type_identity]") {
  using namespace mge;
  using namespace mge::traits;

  SECTION("IsSame Verification") {
    STATIC_REQUIRE(IsSame<int, int>::Value);
    STATIC_REQUIRE(IsSameV<int, int>);
    STATIC_REQUIRE(IsSameV<const float, const float>);
    STATIC_REQUIRE(IsSameV<void*, void*>);
    STATIC_REQUIRE(IsSameV<A, A>);

    STATIC_REQUIRE_FALSE(IsSame<int, float>::Value);
    STATIC_REQUIRE_FALSE(IsSameV<int, float>);
    STATIC_REQUIRE_FALSE(IsSameV<A, B>);

    STATIC_REQUIRE_FALSE(IsSameV<int, const int>);
    STATIC_REQUIRE_FALSE(IsSameV<int, int&>);
    STATIC_REQUIRE_FALSE(IsSameV<A, volatile A>);
  }

  SECTION("IsConst / IsVolatile / IsCV Verification") {
    STATIC_REQUIRE(IsConstV<const int>);
    STATIC_REQUIRE(IsConstV<const volatile int>);
    STATIC_REQUIRE(IsConstV<const A>);
    STATIC_REQUIRE_FALSE(IsConstV<int>);
    STATIC_REQUIRE_FALSE(IsConstV<volatile int>);
    STATIC_REQUIRE_FALSE(IsConstV<B>);

    STATIC_REQUIRE(IsVolatileV<volatile int>);
    STATIC_REQUIRE(IsVolatileV<const volatile int>);
    STATIC_REQUIRE(IsVolatileV<volatile A>);
    STATIC_REQUIRE_FALSE(IsVolatileV<int>);
    STATIC_REQUIRE_FALSE(IsVolatileV<const int>);
    STATIC_REQUIRE_FALSE(IsVolatileV<B>);

    STATIC_REQUIRE(IsCVV<const int>);
    STATIC_REQUIRE(IsCVV<volatile int>);
    STATIC_REQUIRE(IsCVV<const volatile int>);
    STATIC_REQUIRE(IsCVV<const volatile A>);
    STATIC_REQUIRE_FALSE(IsCVV<int>);
    STATIC_REQUIRE_FALSE(IsCVV<B>);
  }

  SECTION("Reference Verification") {
    STATIC_REQUIRE(IsLvalueReferenceV<int&>);
    STATIC_REQUIRE(IsLvalueReferenceV<A&>);
    STATIC_REQUIRE_FALSE(IsLvalueReferenceV<int&&>);
    STATIC_REQUIRE_FALSE(IsLvalueReferenceV<int>);
    STATIC_REQUIRE_FALSE(IsLvalueReferenceV<B>);

    STATIC_REQUIRE(IsRvalueReferenceV<int&&>);
    STATIC_REQUIRE(IsRvalueReferenceV<A&&>);
    STATIC_REQUIRE_FALSE(IsRvalueReferenceV<int&>);
    STATIC_REQUIRE_FALSE(IsRvalueReferenceV<int>);
    STATIC_REQUIRE_FALSE(IsRvalueReferenceV<B>);

    STATIC_REQUIRE(IsReferenceV<int&>);
    STATIC_REQUIRE(IsReferenceV<int&&>);
    STATIC_REQUIRE(IsReferenceV<A&>);
    STATIC_REQUIRE(IsReferenceV<A&&>);
    STATIC_REQUIRE_FALSE(IsReferenceV<int>);
    STATIC_REQUIRE_FALSE(IsReferenceV<B>);
  }

  SECTION("IsCArray Verification") {
    STATIC_REQUIRE(IsCArray<int[5]>::Value);
    STATIC_REQUIRE(IsCArrayV<int[5]>);
    STATIC_REQUIRE(IsCArrayV<char[256]>);
    STATIC_REQUIRE(IsCArrayV<A[128]>);

    STATIC_REQUIRE(IsCArray<int[]>::Value);
    STATIC_REQUIRE(IsCArrayV<int[]>);
    STATIC_REQUIRE(IsCArrayV<double[]>);
    STATIC_REQUIRE(IsCArrayV<B[]>);

    STATIC_REQUIRE_FALSE(IsCArray<int>::Value);
    STATIC_REQUIRE_FALSE(IsCArrayV<int*>);
    STATIC_REQUIRE_FALSE(IsCArrayV<float&>);
    STATIC_REQUIRE_FALSE(IsCArrayV<A>);
    STATIC_REQUIRE_FALSE(IsCArrayV<B>);
  }

  SECTION("IsClass Verification") {
    STATIC_REQUIRE(IsClassV<A>);
    STATIC_REQUIRE(IsClassV<const A>);
    STATIC_REQUIRE_FALSE(IsClassV<int>);
    STATIC_REQUIRE_FALSE(IsClassV<U>); // Union is not Class
  }

  SECTION("IsUnion Verification") {
    STATIC_REQUIRE(IsUnionV<U>);
    STATIC_REQUIRE(IsUnionV<const U>);
    STATIC_REQUIRE_FALSE(IsUnionV<A>);
    STATIC_REQUIRE_FALSE(IsUnionV<int>);
  }

  SECTION("IsNullPointer Verification") {
    STATIC_REQUIRE(IsNullPointerV<null_type>);
    STATIC_REQUIRE(IsNullPointerV<const null_type>);
    STATIC_REQUIRE_FALSE(IsNullPointerV<int*>);
    STATIC_REQUIRE_FALSE(IsNullPointerV<int>);
  }

  SECTION("IsVoid Verification") {
    STATIC_REQUIRE(IsVoid<void>::Value);
    STATIC_REQUIRE(IsVoid<const void>::Value);
    STATIC_REQUIRE(IsVoidV<volatile void>);
    STATIC_REQUIRE(IsVoidV<const volatile void>);

    STATIC_REQUIRE_FALSE(IsVoid<int>::Value);
    STATIC_REQUIRE_FALSE(IsVoidV<double>);
    STATIC_REQUIRE_FALSE(IsVoidV<A>);
    STATIC_REQUIRE_FALSE(IsVoidV<B>);
  }

  SECTION("IsFunction Verification") {
    STATIC_REQUIRE(IsFunction<decltype(func)>::Value);

    STATIC_REQUIRE_FALSE(IsFunctionV<decltype(&func)>);
    auto lambda = [](){};
    STATIC_REQUIRE_FALSE(IsFunctionV<decltype(lambda)>);
  }
}
