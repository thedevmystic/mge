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
 * @file integral_properties.hpp
 * @brief Consolidated query and transformation type traits for integral properties.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following classification and transformation traits:
 * - `is_signed` / `is_signed_v`      : Checks if a given type is a signed type.
 * - `is_unsigned` / `is_unsigned_v`  : Checks if a given type is an unsigned type.
 * - `make_signed` / `make_signed_t`      : Transforms a type into signed type.
 * - `make_unsigned` / `make_unsigned_t`  : Transforms a type into unsigned type.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/core.hpp"
#include "traits/cv_traits.hpp"
#include "traits/primary_classification.hpp"
#include "traits/relationships.hpp"
#include "traits/secondary_classification.hpp"

// #region Detail
namespace mge::traits::detail {

// #region Signed Query Type Trait
/** @brief is_signed sub helper. */
template <typename T, bool = is_integral_v<T>>
struct is_signed_sub_helper : integral_constant<bool, T(-1) < T(0)> {};

/** @brief If not integral (i.e., floating point), then always true. */
template <typename T>
struct is_signed_sub_helper<T, false> : true_type {};

/** @brief is_signed helper. */
template <typename T, bool = is_arithmetic_v<T>>
struct is_signed_helper : is_signed_sub_helper<T> {};

/** @brief If not arithmetic, then always false. */
template <typename T>
struct is_signed_helper<T, false> : false_type {};
// #endregion

// #region Ununsigned Query Type Trait
/** @brief is_unsigned sub helper. */
template <typename T, bool = is_integral_v<T>>
struct is_unsigned_sub_helper : integral_constant<bool, T(0) < T(-1)> {};  // wrap around

/** @brief If not integral (i.e., floating point), then always false. */
template <typename T>
struct is_unsigned_sub_helper<T, false> : false_type {};

/** @brief is_unsigned helper. */
template <typename T, bool = is_arithmetic_v<T>>
struct is_unsigned_helper : is_unsigned_sub_helper<T> {};

/** @brief If not arithmetic, then always false. */
template <typename T>
struct is_unsigned_helper<T, false> : false_type {};
// #endregion

// #region Signed Transformation Type Trait
namespace make_signed_impl {
/** Strip cv-qualifiers. */
template <typename T>
using base_type = remove_cv_t<T>;
/** Map unsigned types to signed counterparts, pass if already signed. */
// clang-format off
template <typename T>
using signed_base_type = 
  conditional_t<is_same_v<base_type<T>, unsigned char>,      signed char,
  conditional_t<is_same_v<base_type<T>, unsigned short>,     short,
  conditional_t<is_same_v<base_type<T>, unsigned int>,       int,
  conditional_t<is_same_v<base_type<T>, unsigned long>,      long,
  conditional_t<is_same_v<base_type<T>, unsigned long long>, long long,
  conditional_t<is_same_v<base_type<T>, char>,               signed char,
  conditional_t<is_same_v<base_type<T>, wchar_t>,            int,
  conditional_t<is_same_v<base_type<T>, char8_t>,            signed char,
  conditional_t<is_same_v<base_type<T>, char16_t>,           short,
  conditional_t<is_same_v<base_type<T>, char32_t>,           int,
  // Already signed — pass through
  base_type<T>
  >>>>>>>>>>;
// clang-format on
/** Re-apply const. */
template <typename T>
using with_const =
    conditional_t<is_const_v<T>, add_const_t<signed_base_type<T>>, signed_base_type<T>>;
/** Re-apply volatile. */
template <typename T>
using with_volatile = conditional_t<is_volatile_v<T>, add_volatile_t<with_const<T>>, with_const<T>>;
}  // namespace make_signed_impl

/** @brief make_signed helper. */
template <typename T>
struct make_signed_helper {
  static_assert(is_integral_v<T> && !is_same_v<T, bool>,
                "make_signed requires an integral type except bool.");
  using type = make_signed_impl::with_volatile<T>;
};
// #endregion

// #region Unsigned Transformation Type Trait
namespace make_unsigned_impl {
/** Strip cv-qualifiers. */
template <typename T>
using base_type = remove_cv_t<T>;
/** Map signed types to unsigned counterparts, pass if already unsigned. */
// clang-format off
template <typename T>
using unsigned_base_type = 
  conditional_t<is_same_v<base_type<T>, signed char>,      unsigned char,
  conditional_t<is_same_v<base_type<T>, short>,            unsigned short,
  conditional_t<is_same_v<base_type<T>, int>,              unsigned int,
  conditional_t<is_same_v<base_type<T>, long>,             unsigned long,
  conditional_t<is_same_v<base_type<T>, long long>,        unsigned long long,
  conditional_t<is_same_v<base_type<T>, char>,             unsigned char,
  conditional_t<is_same_v<base_type<T>, wchar_t>,          unsigned int,
  conditional_t<is_same_v<base_type<T>, char8_t>,          unsigned char,
  conditional_t<is_same_v<base_type<T>, char16_t>,         unsigned short,
  conditional_t<is_same_v<base_type<T>, char32_t>,         unsigned int,
  // Already unsigned — pass through
  base_type<T>
  >>>>>>>>>>;
// clang-format on
/** Re-apply const. */
template <typename T>
using with_const =
    conditional_t<is_const_v<T>, add_const_t<unsigned_base_type<T>>, unsigned_base_type<T>>;
/** Re-apply volatile. */
template <typename T>
using with_volatile = conditional_t<is_volatile_v<T>, add_volatile_t<with_const<T>>, with_const<T>>;
}  // namespace make_unsigned_impl

/** @brief make_unsigned helper. */
template <typename T>
struct make_unsigned_helper {
  static_assert(is_integral_v<T> && !is_same_v<T, bool>,
                "make_unsigned requires an integral type except bool.");
  using type = make_unsigned_impl::with_volatile<T>;
};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

// #region Integral Property - Signed Query
/**
 * @brief A type used to check if an object is a signed type.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_signed : detail::is_signed_helper<T> {};

/**
 * @brief Value alias for is_signed.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_signed_v = is_signed<T>::value;
// #endregion

// #region Integral Property - Unsigned Query
/**
 * @brief A type used to check if an object is a unsigned type.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_unsigned : detail::is_unsigned_helper<T> {};

/**
 * @brief Value alias for is_unsigned.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_unsigned_v = is_unsigned<T>::value;
// #endregion

// #region Integral Property - Signed Transformation
/**
 * @brief A type used to convert an object into a signed type.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE make_signed : detail::make_signed_helper<T> {};

/**
 * @brief Type alias for make_signed.
 * @ingroup traits
 */
template <typename T>
using make_signed_t = typename make_signed<T>::type;
// #endregion

// #region Integral Property - Unsigned Transformation
/**
 * @brief A type used to convert an object into a unsigned type.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE make_unsigned : detail::make_unsigned_helper<T> {};

/**
 * @brief Type alias for make_unsigned.
 * @ingroup traits
 */
template <typename T>
using make_unsigned_t = typename make_unsigned<T>::type;
// #endregion

}  // namespace mge::traits
// #endregion
