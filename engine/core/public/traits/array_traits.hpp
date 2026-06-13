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
 * - `is_unbounded_array` / `is_unbounded_array_v` : Checks if a given type is a unbounded array.
 * - `is_bounded_array` / `is_bounded_array_v`     : Checks if a given type is a bounded array.
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

// #region Unbounded Array Type Trait Helper
/** @brief is_unbounded_array helper. */
template <typename T>
struct is_unbounded_array_helper : false_type {};

/** @brief If unbounded array, then true. */
template <typename T>
struct is_unbounded_array_helper<T[]> : true_type {};
// #endregion

// #region Bounded Array Type Trait Helper
/** @brief is_bounded_array helper. */
template <typename T>
struct is_bounded_array_helper : false_type {};

/** @brief If bounded array, then true. */
template <typename T, size_t N>
struct is_bounded_array_helper<T[N]> : true_type {};
// #endregion

// #region Remove Extent Type Trait Helper
/** @brief remove_extent helper. */
template <typename T>
struct remove_extent_helper {
  using type = T;
};

/** @brief If an array, then strip it. */
template <typename T>
struct remove_extent_helper<T[]> {
  using type = T;
};

template <typename T, size_t N>
struct remove_extent_helper<T[N]> {
  using type = T;
};
// #endregion

// #region Remove All Extents Type Trait Helper
/** @brief remove_all_extents helper. */
template <typename T>
struct remove_all_extents_helper {
  using type = T;
};

/** @brief If an array, then recursively strip it. */
template <typename T>
struct remove_all_extents_helper<T[]> {
  using type = typename remove_all_extents_helper<T>::type;
};

template <typename T, size_t N>
struct remove_all_extents_helper<T[N]> {
  using type = typename remove_all_extents_helper<T>::type;
};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

// #region Array Traits - Rank
/**
 * @brief A type used to check the number of dimensions of an array.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE rank : detail::rank_helper<T> {};

/**
 * @brief Value alias for rank.
 * @ingroup traits
 */
template <typename T>
inline constexpr size_t rank_v = rank<T>::value;
// #endregion

// #region Array Traits - Extent
/**
 * @brief A type used to check the size of a specific dimension in an array.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE extent : detail::extent_helper<T> {};

/**
 * @brief Value alias for extent.
 * @ingroup traits
 */
template <typename T>
inline constexpr size_t extent_v = extent<T>::value;
// #endregion

// #region Array Traits - Unbound Array
/**
 * @brief A type used to check if an object is unbound array.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_unbounded_array : detail::is_unbounded_array_helper<T> {};

/**
 * @brief Value alias for is_unbounded_array.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_unbounded_array_v = is_unbounded_array<T>::value;
// #endregion

// #region Array Traits - Bound Array
/**
 * @brief A type used to check if an object is bound array.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_bounded_array : detail::is_bounded_array_helper<T> {};

/**
 * @brief Value alias for is_bounded_array.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_bounded_array_v = is_bounded_array<T>::value;
// #endregion

// #region Array Traits - Remove Extent
/**
 * @brief A type used to remove the outermost dimension from an array.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE remove_extent : detail::remove_extent_helper<T> {};

/**
 * @brief Value alias for remove_extent.
 * @ingroup traits
 */
template <typename T>
using remove_extent_t = typename remove_extent<T>::type;
// #endregion

// #region Array Traits - Remove All Extents
/**
 * @brief A type used to remove all dimensions from an array.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE remove_all_extents : detail::remove_all_extents_helper<T> {};

/**
 * @brief Value alias for remove_all_extents.
 * @ingroup traits
 */
template <typename T>
using remove_all_extents_t = typename remove_all_extents<T>::type;
// #endregion

}  // namespace mge::traits
// #endregion
