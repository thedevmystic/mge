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
 * @brief Consolidated transformation type traits for adding or stripping pointers.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following type modifiers:
 * - `add_pointer` / `add_pointer_t`        : Adds pointer `(*)`.
 * - `remove_pointer` / `remove_pointer_t`  : Strips pointer `(*)`.
 *   
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/core.hpp"
#include "traits/primary_classification.hpp"
#include "traits/reference_transformations.hpp"

// #region Detail
namespace mge::traits::detail {

// #region Add Pointer Type Trait Helper
/** @brief add_pointer helper. */
template <typename T, bool = reference_transformations::is_referenceable<T>::value || is_void_v<T>>
struct add_pointer_helper {
  using type = typename remove_reference<T>::type*;
};

/** @brief If type is invalid, then we can't add pointer. */
template <typename T>
struct add_pointer_helper<T, false> {
  using type = T;
};
// #endregion

// #region Remove Pointer Type Trait Helper
/** @brief remove_pointer helper. */
template <typename T>
struct remove_pointer_helper {
  using type = T;
};

/** @brief If type is a pointer, strip it. */
template <typename T>
struct remove_pointer_helper<T*> {
  using type = T;
};
template <typename T>
struct remove_pointer_helper<T* const> {
  using type = T;
};
template <typename T>
struct remove_pointer_helper<T* volatile> {
  using type = T;
};
template <typename T>
struct remove_pointer_helper<T* const volatile> {
  using type = T;
};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

// #region Pointer Transformations - Add Pointer
/**
 * @brief type trait to add pointer.
 * @tparam T type of value.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE add_pointer : detail::add_pointer_helper<T> {};

/**
 * @brief type alias add_pointer.
 * @ingroup traits
 */
template <typename T>
using add_pointer_t = typename add_pointer<T>::type;
// #endregion

// #region Pointer Transformations - Remove Pointer
/**
 * @brief type trait to remove pointer.
 * @tparam T type of value.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE remove_pointer : detail::remove_pointer_helper<T> {};

/**
 * @brief type alias remove_pointer.
 * @ingroup traits
 */
template <typename T>
using remove_pointer_t = typename remove_pointer<T>::type;
// #endregion

}  // namespace mge::traits
// #endregion
