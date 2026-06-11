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
 * @file reference_transformations.hpp
 * @brief Consolidated transformation type traits for adding or stripping references.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following type modifiers:
 *  - `add_lvalue_reference` / `add_lvalue_reference_t` : Adds lvalue `&` reference.
 *  - `add_rvalue_reference` / `add_rvalue_reference_t` : Adds rvalue `&&` reference.
 *  - `remove_reference` / `remove_reference_t`    : Strips lvalue `&` and rvalue `&&` references.
 *  - `remove_cvref` / `remove_cvref_t`            : Strips `const`, `volatile`, and reference.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/core.hpp"

// #region Detail
namespace mge::traits::detail {

// #region Local Remove CV-Qualifiers
namespace reference_transformations {
template <typename T>
struct local_remove_cv {
  using type = T;
};
template <typename T>
struct local_remove_cv<const T> {
  using type = T;
};
template <typename T>
struct local_remove_cv<volatile T> {
  using type = T;
};
template <typename T>
struct local_remove_cv<const volatile T> {
  using type = T;
};
} // namespace reference_transformations
// #endregion

// #region Internal Referenceable type Trait Helper
namespace reference_transformations {
namespace is_referenceable_impl {
struct size_two {
  char tag[2];
};
template <typename T>
T& test(int);
template <typename T>
size_two test(...);
} // namespace is_referenceable_impl

/** @brief Checks a type, if it can be referenced. */
template <typename T>
struct is_referenceable : integral_constant<bool, sizeof(is_referenceable_impl::test<T>(0)) != 2> {};
} // namespace reference_transformations
// #endregion

// #region Add Lvalue Reference type Trait Helper
/** @brief add_lvalue_reference helper. */
template <typename T, bool = reference_transformations::is_referenceable<T>::value>
struct add_lvalue_reference_helper {
  using type = T;
};

/** @brief If type is referenceable, then add lvalue reference. */
template <typename T>
struct add_lvalue_reference_helper<T, true> {
  using type = T&;
};
// #endregion

// #region Add Rvalue Reference type Trait Helper
/** @brief add_rvalue_reference helper. */
template <typename T, bool = reference_transformations::is_referenceable<T>::value>
struct add_rvalue_reference_helper {
  using type = T;
};

/** @brief If type is referenceable, then add rvalue reference. */
template <typename T>
struct add_rvalue_reference_helper<T, true> {
  using type = T&&;
};
// #endregion

// #region Remove Reference type Trait Helper
/** @brief remove_reference helper. */
template <typename T>
struct remove_reference_helper {
  using type = T;
};

/** @brief If reference, then strip. */
template <typename T>
struct remove_reference_helper<T&> {
  using type = T;
};

template <typename T>
struct remove_reference_helper<T&&> {
  using type = T;
};
// #endregion

// #region Remove Reference CV-Qualifiers type Trait Helper
/** @brief remove_cvref helper. */
template <typename T>
struct remove_cvref_helper {
  using type = typename reference_transformations::local_remove_cv<typename remove_reference_helper<T>::type>::type;
};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

// #region Reference Transformations - Add Lvalue Reference
/**
 * @brief type trait to add lvalue reference.
 * @tparam T type of value.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE add_lvalue_reference : detail::add_lvalue_reference_helper<T> {};

/**
 * @brief type alias add_lvalue_reference.
 * @ingroup traits
 */
template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
// #endregion

// #region Reference Transformations - Add Rvalue Reference
/**
 * @brief type trait to add rvalue reference.
 * @tparam T type of value.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE add_rvalue_reference : detail::add_rvalue_reference_helper<T> {};

/**
 * @brief type alias add_rvalue_reference.
 * @ingroup traits
 */
template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
// #endregion

// #region Reference Transformations - Remove Reference
/**
 * @brief type trait to remove reference.
 * @tparam T type of value.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE remove_reference : detail::remove_reference_helper<T> {};

/**
 * @brief type alias remove_reference.
 * @ingroup traits
 */
template <typename T>
using remove_reference_t = typename remove_reference<T>::type;
// #endregion

// #region Reference CV-Qualifiers Transformations - Remove Reference CV-Qualifiers
/**
 * @brief type trait to remove reference and cv-qualifiers.
 * @tparam T type of value.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE remove_cvref : detail::remove_cvref_helper<T> {};

/**
 * @brief type alias remove_cvref.
 * @ingroup traits
 */
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;
// #endregion

}  // namespace mge::traits
// #endregion
