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
 * @file secondary_classification.hpp
 * @brief Consolidated type traits for secondary classification of any type.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following identity and classification traits:
 * - `is_reference` \ `is_reference_v`     : Checks if a given type represents a reference type.
 * - `is_arithmetic` \ `is_arithmetic_v`   : Checks if a given type represents a arithmetic type.
 * - `is_fundamental` \ `is_fundamental_v` : Checks if a given type represents a fundamental type.
 * - `is_member_pointer` / `is_member_pointer_v`     : Checks if a given type is a member pointer.
 * - `is_scoped_enum` \ `is_scoped_enum_v`  : Checks if a given type represents a scoped enum type.
 * - `is_scaler` \ `is_scaler_v`     : Checks if a given type represents a scaler type.
 * - `is_object` \ `is_object_v`     : Checks if a given type represents a object type.
 * - `is_compound` \ `is_compound_v` : Checks if a given type represents a compound type.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/core.hpp"
#include "traits/primary_classification.hpp"
#include "utility/declval.hpp"

// #region Detail
namespace mge::traits::detail {

// #region Reference Type Trait Helper
/** @brief is_reference helper. */
template <typename T>
struct is_reference_helper
    : integral_constant<bool, is_lvalue_reference_v<T> || is_rvalue_reference_v<T>> {};
// #endregion

// #region Arithmetic Type Trait Helper
/** @brief is_arithmetic helper. */
template <typename T>
struct is_arithmetic_helper : integral_constant<bool, is_integral_v<T> || is_floating_point_v<T>> {
};
// #endregion

// #region Fundamental Type Trait Helper
/** @brief is_fundamental helper. */
template <typename T>
struct is_fundamental_helper : integral_constant<bool, is_void_v<T> || is_null_pointer_v<T> ||
                                                           is_arithmetic_helper<T>::value> {};
// #endregion

// #region Member Pointer Type Trait Helper
/** @brief is_member_pointer helper. */
template <typename T>
struct is_member_pointer_helper
    : integral_constant<bool, is_member_function_pointer_v<T> || is_member_object_pointer_v<T>> {};
// #endregion

// #region Scoped Enum Type Trait Helper
namespace is_scoped_enum_impl {
struct size_one {
  char tag;
};
struct size_two {
  char tag[2];
};
size_one test(int);
size_two test(...);
}  // namespace is_scoped_enum_impl

/** @brief is_scoped_enum_pointer helper. */
template <typename T, bool = is_enum_v<T>>
struct is_scoped_enum_helper : false_type {};

/** @brief Check for scoped enum, if it is an enum. */
template <typename T>
struct is_scoped_enum_helper<T, true>
    : integral_constant<bool,
                        sizeof(is_scoped_enum_impl::test(::mge::utility::declval<T>())) == 2> {};
// #endregion

// #region Scalar Type Trait Helper
/** @brief is_scalar helper. */
template <typename T>
struct is_scalar_helper
    : integral_constant<bool, is_arithmetic_helper<T>::value ||
                                  is_member_pointer_helper<T>::value || is_pointer_v<T> ||
                                  is_null_pointer_v<T> || is_enum_v<T>> {};
// #endregion

// #region Object Type Trait Helper
/** @brief is_object helper. */
template <typename T>
struct is_object_helper : integral_constant<bool, is_scalar_helper<T>::value || is_array_v<T> ||
                                                      is_class_v<T> || is_union_v<T>> {};
// #endregion

// #region Compound Type Trait Helper
/** @brief is_compound helper. */
template <typename T>
struct is_compound_helper : integral_constant<bool, !is_fundamental_helper<T>::value> {};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

// #region Secondary Classification Trait - Reference
/**
 * @brief A type used to check if an object is reference.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_reference : detail::is_reference_helper<T> {};

/**
 * @brief value alias for is_reference.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_reference_v = is_reference<T>::value;
// #endregion

// #region Secondary Classification Trait - Arithmetic
/**
 * @brief A type used to check if an object is arithmetic.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_arithmetic : detail::is_arithmetic_helper<T> {};

/**
 * @brief value alias for is_arithmetic.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
// #endregion

// #region Secondary Classification Trait - Fundamental
/**
 * @brief A type used to check if an object is fundamental.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_fundamental : detail::is_fundamental_helper<T> {};

/**
 * @brief value alias for is_fundamental.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_fundamental_v = is_fundamental<T>::value;
// #endregion

// #region Secondary Classification Trait - Member Pointer
/**
 * @brief A type used to check if an object is member pointer.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_member_pointer : detail::is_member_pointer_helper<T> {};

/**
 * @brief value alias for is_member_pointer.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_member_pointer_v = is_member_pointer<T>::value;
// #endregion

// #region Secondary Classification Trait - Scoped Enum
/**
 * @brief A type used to check if an object is scoped enum.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_scoped_enum : detail::is_scoped_enum_helper<T> {};

/**
 * @brief value alias for is_scoped_enum.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;
// #endregion

// #region Secondary Classification Trait - Scalar
/**
 * @brief A type used to check if an object is scalar.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_scalar : detail::is_scalar_helper<T> {};

/**
 * @brief value alias for is_scalar.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_scalar_v = is_scalar<T>::value;
// #endregion

// #region Secondary Classification Trait - Object
/**
 * @brief A type used to check if an object is object.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_object : detail::is_object_helper<T> {};

/**
 * @brief value alias for is_object.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_object_v = is_object<T>::value;
// #endregion

// #region Secondary Classification Trait - Compound
/**
 * @brief A type used to check if an object is compound.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_compound : detail::is_compound_helper<T> {};

/**
 * @brief value alias for is_compound.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_compound_v = is_compound<T>::value;
// #endregion

}  // namespace mge::traits
// #endregion
