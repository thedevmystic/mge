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
 * @file logical_operators.hpp
 * @brief Consolidated fundamental compile-time logical operator type traits.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following logical operators:
 * - `conjunction` \ `conjunction_v`           : Logical AND, combines A and B type traits.
 * - `disjunction` \ `disjunction_v`           : Logical OR, combines A or B type traits.
 * - `negation` \ `negation_v`                 : Logical NOT, negates a type trait.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/core.hpp"

// #region Public API
namespace mge::traits {

// #region Logical Operations
/**
 * @brief Compile-time logical AND.
 */
template <typename... Traits>
struct MGE_API_TEMPLATE conjunction : true_type {};

template <typename T, typename... Ts>
struct MGE_API_TEMPLATE conjunction<T, Ts...> : conditional_t<bool(T::value), conjunction<Ts...>, false_type> {};

template <typename... Traits>
inline constexpr bool conjunction_v = conjunction<Traits...>::value;

/**
 * @brief Compile-time logical OR.
 */
template <typename... Traits>
struct MGE_API_TEMPLATE disjunction : false_type {};

template <typename T, typename... Ts>
struct MGE_API_TEMPLATE disjunction<T, Ts...> : conditional_t<bool(T::value), true_type, disjunction<Ts...>> {};

template <typename... Traits>
inline constexpr bool disjunction_v = disjunction<Traits...>::value;

/**
 * @brief Compile-time logical NOT.
 */
template <typename Trait>
struct MGE_API_TEMPLATE negation : bool_constant<!bool(Trait::value)> {};

template <typename Trait>
inline constexpr bool negation_v = negation<Trait>::value;
// #endregion

}  // namespace mge::traits
// #endregion
