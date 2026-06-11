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
 * @file type_modifiers.test.cpp
 * @brief Consolidated verification tests for transformation type traits (stripping qualifiers, references, and extents).
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/type_modifiers.hpp"

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

TEST_CASE("mge::traits - Type Modifiers Verification", "[core][traits][type_modifiers]") {
  using namespace mge::traits;

  SECTION("AddConst Verification") {
    // Const Types
    STATIC_REQUIRE(std::is_same_v<typename AddConst<const int>::Type, const int>);
    STATIC_REQUIRE(std::is_same_v<AddConstT<const volatile float>, const volatile float>);

    // Non-Const Types
    STATIC_REQUIRE(std::is_same_v<typename AddConst<int>::Type, const int>);
    STATIC_REQUIRE(std::is_same_v<AddConstT<volatile double>, const volatile double>);

    // Pointers and Arrays
    STATIC_REQUIRE(std::is_same_v<AddConstT<int*>, int* const>);
    STATIC_REQUIRE(std::is_same_v<AddConstT<int* const>, int* const>);
    STATIC_REQUIRE(std::is_same_v<AddConstT<const int*>, const int* const>);

    // References
    STATIC_REQUIRE(std::is_same_v<AddConstT<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<AddConstT<int&&>, int&&>);
  }

  SECTION("RemoveConst Verification") {
    // Non-Const Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveConst<int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveConstT<volatile float>, volatile float>);

    // Const Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveConst<const int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveConstT<const volatile double>, volatile double>);

    // Pointers and Arrays
    STATIC_REQUIRE(std::is_same_v<RemoveConstT<int* const>, int*>);
    STATIC_REQUIRE(std::is_same_v<RemoveConstT<const int*>, const int*>);
  }

  SECTION("AddVolatile Verification") {
    // Volatile Types
    STATIC_REQUIRE(std::is_same_v<typename AddVolatile<volatile int>::Type, volatile int>);
    STATIC_REQUIRE(std::is_same_v<AddVolatileT<const volatile float>, const volatile float>);

    // Non-Volatile Types
    STATIC_REQUIRE(std::is_same_v<typename AddVolatile<int>::Type, volatile int>);
    STATIC_REQUIRE(std::is_same_v<AddVolatileT<const double>, const volatile double>);

    // Pointers and Arrays
    STATIC_REQUIRE(std::is_same_v<AddVolatileT<int*>, int* volatile>);
    STATIC_REQUIRE(std::is_same_v<AddVolatileT<int* volatile>, int* volatile>);
    STATIC_REQUIRE(std::is_same_v<AddVolatileT<volatile int*>, volatile int* volatile>);

    // References
    STATIC_REQUIRE(std::is_same_v<AddVolatileT<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<AddVolatileT<int&&>, int&&>);
  }

  SECTION("RemoveVolatile Verification") {
    // Non-Volatile Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveVolatile<int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveVolatileT<const float>, const float>);

    // Volatile Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveVolatile<volatile int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveVolatileT<const volatile double>, const double>);

    // Pointers
    STATIC_REQUIRE(std::is_same_v<RemoveVolatileT<int* volatile>, int*>);
    STATIC_REQUIRE(std::is_same_v<RemoveVolatileT<volatile int*>, volatile int*>);
  }

  SECTION("AddCV Verification") {
    // Plain Types
    STATIC_REQUIRE(std::is_same_v<typename AddCV<int>::Type, const volatile int>);
    STATIC_REQUIRE(std::is_same_v<AddCVT<float>, const volatile float>);

    // Fully and Partially Qualified Types
    STATIC_REQUIRE(std::is_same_v<AddCVT<const int>, const volatile int>);
    STATIC_REQUIRE(std::is_same_v<AddCVT<volatile double>, const volatile double>);
    STATIC_REQUIRE(std::is_same_v<AddCVT<const volatile char>, const volatile char>);

    // Pointers
    STATIC_REQUIRE(std::is_same_v<AddCVT<int*>, int* const volatile>);

    // References
    STATIC_REQUIRE(std::is_same_v<AddCVT<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<AddCVT<int&&>, int&&>);
  }

  SECTION("RemoveCV Verification") {
    // Plain Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveCV<int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveCVT<int>, int>);

    // Qualifiers Stripping
    STATIC_REQUIRE(std::is_same_v<typename RemoveCV<const int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveCVT<volatile int>, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveCVT<const volatile int>, int>);

    // Pointers
    STATIC_REQUIRE(std::is_same_v<RemoveCVT<const volatile int* const volatile>, const volatile int*>);
  }

  SECTION("AddLvalueReference Verification") {
    // Plain Types
    STATIC_REQUIRE(std::is_same_v<typename AddLvalueReference<int>::Type, int&>);
    STATIC_REQUIRE(std::is_same_v<AddLvalueReferenceT<float>, float&>);

    // Reference Types
    STATIC_REQUIRE(std::is_same_v<AddLvalueReferenceT<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<AddLvalueReferenceT<int&&>, int&>);

    // Qualified and Pointer Types
    STATIC_REQUIRE(std::is_same_v<AddLvalueReferenceT<const double>, const double&>);
    STATIC_REQUIRE(std::is_same_v<AddLvalueReferenceT<int*>, int*&>);
  }

  SECTION("AddRvalueReference Verification") {
    // Plain Types
    STATIC_REQUIRE(std::is_same_v<typename AddRvalueReference<int>::Type, int&&>);
    STATIC_REQUIRE(std::is_same_v<AddRvalueReferenceT<float>, float&&>);

    // Reference Types
    STATIC_REQUIRE(std::is_same_v<AddRvalueReferenceT<int&>, int&>);
    STATIC_REQUIRE(std::is_same_v<AddRvalueReferenceT<int&&>, int&&>);

    // Qualified and Pointer Types
    STATIC_REQUIRE(std::is_same_v<AddRvalueReferenceT<const double>, const double&&>);
    STATIC_REQUIRE(std::is_same_v<AddRvalueReferenceT<int*>, int*&&>);
  }

  SECTION("RemoveReference Verification") {
    // Non-Reference Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveReference<int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveReferenceT<int*>, int*>);

    // Reference Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveReference<int&>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveReferenceT<const int&>, const int>);

    // Rvalue Reference
    STATIC_REQUIRE(std::is_same_v<typename RemoveReference<int&&>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveReferenceT<volatile int&&>, volatile int>);
  }

  SECTION("RemoveCVRef Verification") {
    // Plain Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveCVRef<int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveCVRefT<float>, float>);

    // Mixed Reference and CV Qualifiers
    STATIC_REQUIRE(std::is_same_v<typename RemoveCVRef<const int&>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveCVRefT<volatile int&&>, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveCVRefT<const volatile double&>, double>);

    // Pointers with Reference Wrappers
    STATIC_REQUIRE(std::is_same_v<RemoveCVRefT<const int* const&>, const int*>);
  }

  SECTION("AddPointer Verification") {
    // Plain Types
    STATIC_REQUIRE(std::is_same_v<typename AddPointer<int>::Type, int*>);
    STATIC_REQUIRE(std::is_same_v<AddPointerT<float>, float*>);

    // Reference Types
    STATIC_REQUIRE(std::is_same_v<AddPointerT<int&>, int*>);
    STATIC_REQUIRE(std::is_same_v<AddPointerT<const float&&>, const float*>);

    // Qualified and Pointer Types
    STATIC_REQUIRE(std::is_same_v<AddPointerT<const int>, const int*>);
    STATIC_REQUIRE(std::is_same_v<AddPointerT<int*>, int**>);
  }

  SECTION("RemovePointer Verification") {
    // Pointer Types
    STATIC_REQUIRE(std::is_same_v<typename RemovePointer<int*>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemovePointerT<const float*>, const float>);
    STATIC_REQUIRE(std::is_same_v<RemovePointerT<int**>, int*>);

    // Qualified Pointer Types
    STATIC_REQUIRE(std::is_same_v<RemovePointerT<int* const>, int>);
    STATIC_REQUIRE(std::is_same_v<RemovePointerT<int* volatile>, int>);
    STATIC_REQUIRE(std::is_same_v<RemovePointerT<int* const volatile>, int>);

    // Non-Pointer Types
    STATIC_REQUIRE(std::is_same_v<RemovePointerT<int>, int>);
    STATIC_REQUIRE(std::is_same_v<RemovePointerT<int&>, int&>);
  }

  SECTION("RemoveExtent Verification") {
    // Non-Array Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveExtent<int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveExtentT<float>, float>);

    // Single Dimension Arrays
    STATIC_REQUIRE(std::is_same_v<typename RemoveExtent<int[]>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveExtentT<int[5]>, int>);

    // Multi-Dimensional Arrays (Should only strip the first dimension)
    STATIC_REQUIRE(std::is_same_v<typename RemoveExtent<int[][10]>::Type, int[10]>);
    STATIC_REQUIRE(std::is_same_v<RemoveExtentT<int[5][10]>, int[10]>);
  }

  SECTION("RemoveAllExtent Verification") {
    // Non-Array Types
    STATIC_REQUIRE(std::is_same_v<typename RemoveAllExtent<int>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveAllExtentT<float>, float>);

    // Single and Multi-Dimensional Arrays
    STATIC_REQUIRE(std::is_same_v<typename RemoveAllExtent<int[]>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveAllExtentT<int[5]>, int>);

    // Completely strip multi-dimensional paths down to the base type
    STATIC_REQUIRE(std::is_same_v<typename RemoveAllExtent<int[][10][20]>::Type, int>);
    STATIC_REQUIRE(std::is_same_v<RemoveAllExtentT<int[5][10][20]>, int>);
  }
}
