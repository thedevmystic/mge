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
 * @file relationships.hpp
 * @brief Consolidated type traits for relationship determination between two types.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following relationship traits:
 * - `is_same` / `is_same_v`   : Checks if two types are the same type.
 * - `is_base_of` / `is_base_of_v`   : Checks if one type is base of the other one.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/core.hpp"

// #region Detail
namespace mge::traits::detail {

// #region Same Type Trait Helper
/** @brief is_same helper. */
template <typename T, typename U>
struct is_same_helper : false_type {};

/** @brief If both are same type, then true. */
template <typename T>
struct is_same_helper<T, T> : true_type {};
// #endregion



// #region Base Of Type Trait Helper
/** @brief is_base_of helper. */
template <typename B, typename D>
struct is_base_of_helper : integral_constant<bool, __is_base_of(B, D)> {};
// #endregion

// #region Virtual Base Of Type Trait Helper
namespace is_virtual_base_of_impl {
struct size_one {
  char tag;
};
struct size_two {
  char tag[2];
};
template <typename T, int N> struct wrap : T {};
template <typename B, typename D>
struct double_derived : wrap<D, 0>, wrap<D, 1> {};
template <typename B, typename D>
size_one test(int, enable_if_t<is_convertible_helper<double_derived<B,D>*, B*>::value, double_derived<B,D>>* = nullptr);
template <typename B, typename D>
size_two test(...);
}  // namespace is_virtual_base_of_impl

/** @brief is_virtual_base_of helper. */
template <typename B, typename D>
struct is_virtual_base_of_helper
    : integral_constant<bool,
                        is_base_of_helper<B, D>::value &&
                            sizeof(is_virtual_base_of_impl::test<B, D>(0, nullptr, nullptr)) != 2> {
};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {}  // namespace mge::traits
// #endregion
