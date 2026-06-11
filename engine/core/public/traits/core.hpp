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
 * @file core.hpp
 * @brief Consolidated foundational metaprogramming primitives and conditional compilation
 *        infrastructure.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following essential meta-building blocks:
 * - `conditional` / `conditional_t`      : Compiles based on provided condition.
 * - `enable_if` / `enable_if_t`          : SFINAE (Substitution Failure Is Not An Error) triggers.
 * - `integral_constant`                  : Standard-style compile-time integral wrappers.
 * - `bool_constant`                      : Specializations for boolean compile-time constants.
 * - `true_type` / `false_type`           : True and false boolean compile-time constants.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"

// #region Public API
namespace mge::traits {

// #region Conditional Compilation (SFINAE)
/**
 * @brief Compile-time type selector trait to choose between two types based on a condition.
 * @tparam Cond The condition of choice.
 * @tparam If The true path.
 * @tparam Then The false path.
 * @ingroup traits
 */
template <bool Cond, typename If, typename Then>
struct MGE_API_TEMPLATE conditional {
  using type = If;
};

/** @brief If condition is false. */
template <typename If, typename Then>
struct MGE_API_TEMPLATE conditional<false, If, Then> {
  using type = Then;
};

/**
 * @brief type alias for conditional.
 * @ingroup traits
 */
template <bool Cond, typename If, typename Then>
using conditional_t = typename conditional<Cond, If, Then>::type;

/**
 * @brief Enable if trait to compile based on conditions.
 * @tparam Cond The condition for compilation.
 * @tparam T The type.
 * @ingroup traits
 */
template <bool Cond, typename T = void>
struct MGE_API_TEMPLATE enable_if {};

/** @brief For true path. */
template <typename T>
struct MGE_API_TEMPLATE enable_if<true, T> {
  using type = T;
};

/**
 * @brief type alias for enable_if.
 * @ingroup traits
 */
template <bool Cond, typename T = void>
using enable_if_t = typename enable_if<Cond, T>::type;
// #endregion

// #region Integral Constants
/**
 * @brief A type used to show a integral value.
 * @tparam T type of the value.
 * @tparam val value.
 * @ingroup traits
 */
template <typename T, T val>
struct MGE_API_TEMPLATE integral_constant {
  static constexpr T value = val;
  using value_type = T;
  using type = integral_constant;

  /** @brief Conversion operator. */
  constexpr operator value_type() const noexcept { return value; }

  /** @brief Function call operator. */
  constexpr value_type operator()() const noexcept { return value; }
};

/**
 * @brief Alias for Boolean type.
 * @ingroup traits
 */
template <bool B>
using bool_constant = integral_constant<bool, B>;

/**
 * @brief True type, holding a true value.
 * @ingroup traits
 */
using true_type = bool_constant<true>;

/**
 * @brief False type, holding a false value.
 * @ingroup traits
 */
using false_type = bool_constant<false>;
// #endregion

}  // namespace mge::traits
// #endregion
