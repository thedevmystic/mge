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
 * @file type_identity.hpp
 * @brief Consolidated type traits for CV-Qualifiers.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following classification and transformation traits:
 * - `is_const` / `is_const_v`               : Checks if a given type is const qualified.
 * - `is_volatile` / `is_volatile_v`         : Checks if a given type is volatile qualified.
 * - `is_cv` / `is_cv_v`                     : Checks if a given type is const or volatile qualified.
 * - `add_const` / `add_const_t`             : Adds `const` qualifiers.
 * - `add_volatile` / `add_volatile_t`       : Adds `volatile` qualifiers.
 * - `add_cv` / `add_cv_t`                   : Adds both `const` and `volatile` qualifiers.
 * - `remove_const` / `remove_const_t`       : Strips `const` qualifiers.
 * - `remove_volatile` / `remove_volatile_t` : Strips `volatile` qualifiers.
 * - `remove_cv` / `remove_cv_t`             : Strips both `const` and `volatile` qualifiers.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/core.hpp"
#include "traits/primary_classification.hpp"
#include "traits/secondary_classification.hpp"

// #region Detail
namespace mge::traits::detail {

// #region CV-Qualifers Query Type Traits Helpers
/** @brief is_const helper. */
template <typename T>
struct is_const_helper : false_type {};

/** @brief If const, then true type. */
template <typename T>
struct is_const_helper<const T> : true_type {};

/** @brief is_volatile helper. */
template <typename T>
struct is_volatile_helper : false_type {};

/** @brief If volatile, then true type. */
template <typename T>
struct is_volatile_helper<volatile T> : true_type {};

/** @brief is_cv helper. */
template <typename T>
struct is_cv_helper : integral_constant<bool, is_const_helper<T>::value || is_volatile_helper<T>::value> {
};
// #endregion

// #region CV-Qualifers Add Type Traits Helpers
/** @brief add_const helper. */
template <typename T, bool = is_reference_v<T> || is_function_v<T> || is_const_helper<T>::value>
struct add_const_helper {
  using type = T;
};

/** @brief If valid, then add const. */
template <typename T>
struct add_const_helper<T, false> {
  using type = const T;
};

/** @brief add_volatile helper. */
template <typename T, bool = is_reference_v<T> || is_function_v<T> || is_volatile_helper<T>::value>
struct add_volatile_helper {
  using type = T;
};

/** @brief If valid, then add volatile. */
template <typename T>
struct add_volatile_helper<T, false> {
  using type = volatile T;
};

/** @brief add_cv helper. */
template <typename T>
struct add_cv_helper {
  using type = typename add_volatile_helper<typename add_const_helper<T>::type>::type;
};
// #endregion

// #region CV-Qualifers Remove Type Traits Helpers
/** @brief remove_const helper. */
template <typename T>
struct remove_const_helper {
  using type = T;
};

/** @brief If const, then strip. */
template <typename T>
struct remove_const_helper<const T> {
  using type = T;
};

/** @brief remove_volatile helper. */
template <typename T>
struct remove_volatile_helper {
  using type = T;
};

/** @brief If volatile, then strip. */
template <typename T>
struct remove_volatile_helper<volatile T> {
  using type = T;
};

/** @brief remove_cv helper. */
template <typename T>
struct remove_cv_helper {
  using type = typename remove_volatile_helper<typename remove_const_helper<T>::type>::type;
};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

// #region CV-Qualifiers Query - Const
/**
 * @brief A type used to check if an object is const.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_const : detail::is_const_helper<T> {};

/**
 * @brief Value alias for is_const.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_const_v = is_const<T>::value;
// #endregion

// #region CV-Qualifiers Query - Volatile
/**
 * @brief A type used to check if an object is volatile.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_volatile : detail::is_volatile_helper<T> {};

/**
 * @brief Value alias for is_volatile.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_volatile_v = is_volatile<T>::value;
// #endregion

// #region CV-Qualifiers Query - CV
/**
 * @brief A type used to check if an object is cv.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_cv : detail::is_cv_helper<T> {};

/**
 * @brief Value alias for is_cv.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_cv_v = is_cv<T>::value;
// #endregion

// #region CV-Qualifiers Add - Const
/**
 * @brief A type used to add const.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE add_const : detail::add_const_helper<T> {};

/**
 * @brief Type alias for add_const.
 * @ingroup traits
 */
template <typename T>
using add_const_t = typename add_const<T>::type;
// #endregion

// #region CV-Qualifiers Add - Volatile
/**
 * @brief A type used to add volatile.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE add_volatile : detail::add_volatile_helper<T> {};

/**
 * @brief Type alias for add_volatile.
 * @ingroup traits
 */
template <typename T>
using add_volatile_t = typename add_volatile<T>::type;
// #endregion

// #region CV-Qualifiers Add - CV
/**
 * @brief A type used to add cv.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE add_cv : detail::add_cv_helper<T> {};

/**
 * @brief Type alias for add_cv.
 * @ingroup traits
 */
template <typename T>
using add_cv_t = typename add_cv<T>::type;
// #endregion

// #region CV-Qualifiers Remove - Const
/**
 * @brief A type used to remove const.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE remove_const : detail::remove_const_helper<T> {};

/**
 * @brief Type alias for remove_const.
 * @ingroup traits
 */
template <typename T>
using remove_const_t = typename remove_const<T>::type;
// #endregion

// #region CV-Qualifiers Remove - Volatile
/**
 * @brief A type used to remove volatile.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE remove_volatile : detail::remove_volatile_helper<T> {};

/**
 * @brief Type alias for remove_volatile.
 * @ingroup traits
 */
template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;
// #endregion

// #region CV-Qualifiers Remove - CV
/**
 * @brief A type used to remove cv.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE remove_cv : detail::remove_cv_helper<T> {};

/**
 * @brief Type alias for remove_cv.
 * @ingroup traits
 */
template <typename T>
using remove_cv_t = typename remove_cv<T>::type;
// #endregion


}  // namespace mge::traits
// #endregion
