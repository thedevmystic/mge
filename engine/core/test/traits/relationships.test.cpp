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
 * @file relationships.test.cpp
 * @brief Consolidated verification tests for type relationship traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#include "traits/relationships.hpp"

#include <catch2/catch_test_macros.hpp>
#include <type_traits>

namespace mge::utility {
// Minimal reference_wrapper stub for test purposes
template <typename T>
struct reference_wrapper {
  T& ref;
  constexpr T& get() const noexcept { return ref; }
};
} // namespace mge::utility

namespace {
struct Base {};
struct Derived : Base {};
struct VirtualDerived : virtual Base {};
struct NonDerived {};
struct Abstract { virtual void pure() = 0; };

struct Callable {
  int operator()(int x) { return x * 2; }
  void no_throw() noexcept {}
};

struct MemberContainer {
  int data_member = 42;
  int func_member(int x) { return x; }
};

struct MultiCallable {
  void operator()(int&) & {}
  void operator()(int&&) && {}
};

struct ComplexBase { int base_data = 1; };
struct ComplexDerived : ComplexBase { int derived_data = 2; };

struct RefQualified {
  void lvalue_only() & {}
  void rvalue_only() && {}
};

struct Immovable {
  Immovable() = default;
  Immovable(const Immovable&) = delete;
  Immovable(Immovable&&) = delete;
};

struct ImmovableConsumer {
  void operator()(const Immovable&) {}
};

struct VariadicCallable {
  template <typename... Args>
  void operator()(Args&&...) {}
};

struct AmbiguousReturn {
  operator int() const { return 42; }
};

struct Source {
  AmbiguousReturn operator()() { return {}; }
};

struct Target {};

struct ConditionalNoexcept {
  void op1() noexcept(true) {}
  void op2() noexcept(false) {}

  template <typename T>
  void op3(T x) noexcept(sizeof(T) == 1) {}
};

struct NothrowConvertibleReturn {
  void op() noexcept {}
};

struct SafeInt {
  // Nothrow conversion operator
  operator int() const noexcept { return 100; }
};

struct NothrowConversionSource {
  SafeInt operator()() noexcept { return {}; }
};
} // namespace

TEST_CASE("mge::traits - Relationship Verification", "[core][traits][relationships]") {
  using namespace mge::traits;

  SECTION("is_same Verification") {
    STATIC_REQUIRE(is_same<int, int>::value);
    STATIC_REQUIRE(is_same_v<int, int>);
    STATIC_REQUIRE(is_same_v<void, void>);
    STATIC_REQUIRE(is_same_v<const int, const int>);
    STATIC_REQUIRE_FALSE(is_same_v<int, const int>);
    STATIC_REQUIRE_FALSE(is_same_v<int, float>);
    STATIC_REQUIRE_FALSE(is_same_v<Base, Derived>);
  }

  SECTION("is_convertible Verification") {
    STATIC_REQUIRE(is_convertible<int, float>::value);
    STATIC_REQUIRE(is_convertible_v<Derived*, Base*>);
    STATIC_REQUIRE(is_convertible_v<int, int>);
    STATIC_REQUIRE_FALSE(is_convertible_v<Base*, Derived*>);
    STATIC_REQUIRE_FALSE(is_convertible_v<int, Abstract>);
  }

  SECTION("is_base_of Verification") {
    STATIC_REQUIRE(is_base_of<Base, Derived>::value);
    STATIC_REQUIRE(is_base_of_v<Base, Derived>);
    STATIC_REQUIRE(is_base_of_v<Base, VirtualDerived>);
    STATIC_REQUIRE(is_base_of_v<Base, Base>); // A class is a base of itself according to the trait
    STATIC_REQUIRE_FALSE(is_base_of_v<Derived, Base>);
    STATIC_REQUIRE_FALSE(is_base_of_v<Base, NonDerived>);
  }

  SECTION("is_virtual_base_of Verification") {
    STATIC_REQUIRE(is_virtual_base_of<Base, VirtualDerived>::value);
    STATIC_REQUIRE(is_virtual_base_of_v<Base, VirtualDerived>);
    STATIC_REQUIRE_FALSE(is_virtual_base_of_v<Base, Derived>);
    STATIC_REQUIRE_FALSE(is_virtual_base_of_v<Base, Base>);
    STATIC_REQUIRE_FALSE(is_virtual_base_of_v<Base, NonDerived>);
  }

  SECTION("is_invocable Verification") {
    STATIC_REQUIRE(is_invocable<Callable, int>::value);
    STATIC_REQUIRE(is_invocable_v<Callable, int>);
    STATIC_REQUIRE_FALSE(is_invocable_v<Callable, Base>); // Invalid argument type
    STATIC_REQUIRE_FALSE(is_invocable_v<NonDerived, int>); // Not a callable type

    // Pointer-to-member function invocations
    STATIC_REQUIRE(is_invocable_v<int (MemberContainer::*)(int), MemberContainer*, int>);
    STATIC_REQUIRE(is_invocable_v<int (MemberContainer::*)(int), MemberContainer&, int>);

    // Pointer-to-member data object access
    STATIC_REQUIRE(is_invocable_v<int MemberContainer::*, MemberContainer*>);
    STATIC_REQUIRE(is_invocable_v<int MemberContainer::*, MemberContainer&>);

    // Advanced Value category & cv-qualification overloads
    STATIC_REQUIRE(is_invocable_v<MultiCallable&, int&>);
    STATIC_REQUIRE_FALSE(is_invocable_v<MultiCallable&&, int&>);
    STATIC_REQUIRE(is_invocable_v<MultiCallable&&, int&&>);
    STATIC_REQUIRE_FALSE(is_invocable_v<const MultiCallable&, int&>);

    // Contravariant pointer-to-member checks
    STATIC_REQUIRE(is_invocable_v<int ComplexBase::*, ComplexDerived*>);
    STATIC_REQUIRE(is_invocable_v<int ComplexBase::*, ComplexDerived&>);
    STATIC_REQUIRE(is_invocable_v<int ComplexBase::*, mge::utility::reference_wrapper<ComplexDerived>>);

    // Member function pointers with ref-qualifiers
    STATIC_REQUIRE(is_invocable_v<void (RefQualified::*)(), RefQualified&>);
    STATIC_REQUIRE_FALSE(is_invocable_v<void (RefQualified::*)() &, RefQualified&&>);

    // Non-Copyable / Non-Movable arguments validation
    STATIC_REQUIRE(is_invocable_v<ImmovableConsumer, const Immovable&>);
    STATIC_REQUIRE(is_invocable_v<ImmovableConsumer, Immovable&>);

    // Variadics and Ellipses
    STATIC_REQUIRE(is_invocable_v<VariadicCallable>);
    STATIC_REQUIRE(is_invocable_v<VariadicCallable, int, float, char, double, void*>);
  }

  SECTION("is_invocable_r Verification") {
    STATIC_REQUIRE(is_invocable_r<int, Callable, int>::value);
    STATIC_REQUIRE(is_invocable_r_v<int, Callable, int>);
    STATIC_REQUIRE(is_invocable_r_v<void, Callable, int>); // void indicates return value is ignored
    STATIC_REQUIRE(is_invocable_r_v<float, Callable, int>); // convertible return type
    STATIC_REQUIRE_FALSE(is_invocable_r_v<Base, Callable, int>); // cannot convert int to Base

    // Strict return conversions via user-defined operators
    STATIC_REQUIRE(is_invocable_r_v<int, Source>);
    STATIC_REQUIRE(is_invocable_r_v<void, Source>);
    STATIC_REQUIRE_FALSE(is_invocable_r_v<Target, Source>);
  }

  SECTION("is_nothrow_invocable Verification") {
    STATIC_REQUIRE(is_nothrow_invocable<decltype(&Callable::no_throw), Callable>::value);
    STATIC_REQUIRE(is_nothrow_invocable_v<decltype(&Callable::no_throw), Callable>);
    STATIC_REQUIRE_FALSE(is_nothrow_invocable_v<Callable, int>); // operator() is not noexcept

    // Dependent & static noexcept evaluation checks
    STATIC_REQUIRE(is_nothrow_invocable_v<decltype(&ConditionalNoexcept::op1), ConditionalNoexcept>);
    STATIC_REQUIRE_FALSE(is_nothrow_invocable_v<decltype(&ConditionalNoexcept::op2), ConditionalNoexcept>);
    STATIC_REQUIRE(is_nothrow_invocable_v<decltype(&ConditionalNoexcept::op3<char>), ConditionalNoexcept, char>);
    STATIC_REQUIRE_FALSE(is_nothrow_invocable_v<decltype(&ConditionalNoexcept::op3<int>), ConditionalNoexcept, int>);
  }

  SECTION("is_nothrow_invocable_r Verification") {
    STATIC_REQUIRE(is_nothrow_invocable_r<void, decltype(&Callable::no_throw), Callable>::value);
    STATIC_REQUIRE(is_nothrow_invocable_r_v<void, decltype(&Callable::no_throw), Callable>);
    STATIC_REQUIRE_FALSE(is_nothrow_invocable_r_v<void, Callable, int>);

    // Strict nothrow return conversion checks
    STATIC_REQUIRE(is_nothrow_invocable_r_v<void, decltype(&NothrowConvertibleReturn::op), NothrowConvertibleReturn>);
    STATIC_REQUIRE(is_nothrow_invocable_r_v<int, NothrowConversionSource>);
    STATIC_REQUIRE_FALSE(is_nothrow_invocable_r_v<void, ConditionalNoexcept, int>); // throws
  }
}
