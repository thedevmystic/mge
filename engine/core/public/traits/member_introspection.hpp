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
 * @file pointer_transformations.hpp
 * @brief Consolidated type traits for introspection of any type.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following classification traits:
 * - `is_standard_layout` / 
 *   `is_standard_layout_v`    : Checks if a given type represents a standard layout type.
 * - `is_trivially_copyable` / 
 *   `is_trivially_copyable_v` : Checks if a given type represents a  trivially copyable type.
 * - `is_pod` / `is_pod_v`                  : Checks if a given type represents a pod type.
 * - `is_trivial` / `is_trivial_v`          : Checks if a given type represents a trivial type.
 * - `is_empty` / `is_empty_v`              : Checks if a given type represents a empty type.
 * - `is_polymorphic` / `is_polymorphic_v`  : Checks if a given type represents a polymorphic type.
 * - `is_abstract` / `is_abstract_v`        : Checks if a given type represents a abstract type.
 * - `is_final` / `is_final_v`              : Checks if a given type represents a final type.
 * - `is_aggregate` / `is_aggregate_v`      : Checks if a given type represents a aggregate type.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/core.hpp"

// #region Detail
namespace mge::traits::detail {

// #region Standard Layout Type Trait Helper
/** @brief is_standard_layout helper. */
template <typename T>
struct is_standard_layout_helper : integral_constant<bool, __is_standard_layout(T)> {};
// #endregion

// #region Trivially Copyable Type Trait Helper
template <typename T>
/** @brief is_trivially_copyable helper. */
struct is_trivially_copyable_helper : integral_constant<bool, __is_trivially_copyable(T)> {};
// #endregion

// #region POD Type Trait Helper
template <typename T>
/** @brief is_pod helper. */
struct is_pod_helper : integral_constant<bool, __is_pod(T)> {};
// #endregion

// #region Trivial Type Trait Helper
template <typename T>
/** @brief is_trivial helper. */
struct is_trivial_helper : integral_constant<bool, __is_trivial(T)> {};
// #endregion

// #region Empty Type Trait Helper
template <typename T>
/** @brief is_empty helper. */
struct is_empty_helper : integral_constant<bool, __is_empty(T)> {};
// #endregion

// #region Polymorphic Type Trait Helper
template <typename T>
/** @brief is_polymorphic helper. */
struct is_polymorphic_helper : integral_constant<bool, __is_polymorphic(T)> {};
// #endregion

// #region Abstract Type Trait Helper
template <typename T>
/** @brief is_abstract helper. */
struct is_abstract_helper : integral_constant<bool, __is_abstract(T)> {};
// #endregion

// #region Final Type Trait Helper
template <typename T>
/** @brief is_final helper. */
struct is_final_helper : integral_constant<bool, __is_final(T)> {};
// #endregion

// #region Aggregate Type Trait Helper
template <typename T>
/** @brief is_aggregate helper. */
struct is_aggregate_helper : integral_constant<bool, __is_aggregate(T)> {};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

// #region Member Introspection Trait - Standard Layout
/**
 * @brief A type used to check if an object is standard layout.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_standard_layout : detail::is_standard_layout_helper<T> {};

/**
 * @brief value alias for is_standard_layout.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_standard_layout_v = is_standard_layout<T>::value;
// #endregion

// #region Member Introspection Trait - Trivially Copyable
/**
  @brief A type used to check if an object is trivially copyable.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_trivially_copyable : detail::is_trivially_copyable_helper<T> {};

/**
 * @brief value alias for is_trivially_copyable.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;
// #endregion

// #region Member Introspection Trait - POD
/**
 * @brief A type used to check if an object is pod.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_pod : detail::is_pod_helper<T> {};

/**
 * @brief value alias for is_pod.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_pod_v = is_pod<T>::value;
// #endregion

// #region Member Introspection Trait - Trivial
/**
 * @brief A type used to check if an object is trivial.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_trivial : detail::is_trivial_helper<T> {};

/**
 * @brief value alias for is_trivial.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_trivial_v = is_trivial<T>::value;
// #endregion

// #region Member Introspection Trait - Empty
/**
 * @brief A type used to check if an object is empty.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_empty : detail::is_empty_helper<T> {};

/**
 * @brief value alias for is_empty.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_empty_v = is_empty<T>::value;
// #endregion

// #region Member Introspection Trait - Polymorphic
/**
 * @brief A type used to check if an object is polymorphic.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_polymorphic : detail::is_polymorphic_helper<T> {};

/**
 * @brief value alias for is_polymorphic.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_polymorphic_v = is_polymorphic<T>::value;
// #endregion

// #region Member Introspection Trait - Abstract
/**
 * @brief A type used to check if an object is abstract.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_abstract : detail::is_abstract_helper<T> {};

/**
 * @brief value alias for is_abstract.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_abstract_v = is_abstract<T>::value;
// #endregion

// #region Member Introspection Trait - Final
/**
 * @brief A type used to check if an object is final.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_final : detail::is_final_helper<T> {};

/**
 * @brief value alias for is_final.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_final_v = is_final<T>::value;
// #endregion

// #region Member Introspection Trait - Aggregate
/**
 * @brief A type used to check if an object is aggregate.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_aggregate : detail::is_aggregate_helper<T> {};

/**
 * @brief value alias for is_aggregate.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_aggregate_v = is_aggregate<T>::value;
// #endregion

}  // namespace mge::traits
// #endregion
