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
 * @file array_traits.hpp
 * @brief Consolidated type traits for Arrays.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following classification and transformation traits:
 * - `rank` / `rank_v`                 : Returns the total number of dimensions of an array.
 * - `extent` / `extent_v`             : Returns the size of an specific dimension of an array.
 * - `is_bounded_array` / `is_bounded_array_v`     : Checks if a given type is a bounded array.
 * - `is_unbounded_array` / `is_unbounded_array_v` : Checks if a given type is a unbounded array.
 * - `remove_extent` / `remove_extent_t`           : Strips a single dimension from the array.
 * - `remove_all_extent` / `remove_all_extent_t`   : Strips all dimension from the array.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "common/types.hpp"
#include "traits/core.hpp"

// #region Detail
namespace mge::traits::detail {

// #region Rank Type Trait Helper
/** @brief rank helper. */
template <typename T>
struct rank_helper : integral_constant<size_t, 0> {};

/** @brief Recursively find all dimensions. */
template <typename T>
struct rank_helper<T[]> : integral_constant<size_t, rank_helper<T>::value + 1> {};

template <typename T, size_t N>
struct rank_helper<T[N]> : integral_constant<size_t, rank_helper<T>::value + 1> {};
// #endregion

// #region Extent Type Trait Helper
/** @brief extent helper. */
template <typename T, unsigned U = 0>
struct extent_helper : integral_constant<size_t, 0> {};

template <typename T>
struct extent_helper<T[], 0> : integral_constant<size_t, 0> {};

template <typename T, unsigned U>
struct extent_helper<T[], U> : integral_constant<size_t, extent_helper<T, U - 1>::value> {};
  
template <typename T, size_t N>
struct extent_helper<T[N], 0> : integral_constant<size_t, N> {};

template <typename T, size_t N, unsigned U>
struct extent_helper<T[N], U> : integral_constant<size_t, extent_helper<T, U - 1>::value> {};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

}  // namespace mge::traits
// #endregion
