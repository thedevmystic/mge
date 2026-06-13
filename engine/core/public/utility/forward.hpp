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
 * @file declval.hpp
 * @brief Defines forward utility helper for perfect forwarding.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/primary_classification.hpp"
#include "traits/reference_transformations.hpp"

namespace mge::utility {

/**
 * @brief Forward utility to perfectly forward any argument (preserving references).
 * @tparam T Type of the object.
 * @returns Reference of the object `(T)` (preserved lvalue or rvalue).
 * @ingroup utility
 */
template <typename T>
constexpr T&& forward(::mge::traits::remove_reference_t<T>& t) noexcept {
  return static_cast<T&&>(t);
}

template <typename T>
constexpr T&& forward(::mge::traits::remove_reference_t<T>&& t) noexcept {
  static_assert(!::mge::traits::is_lvalue_reference_v<T>,
                "template argument substituting T is an lvalue reference type");
  return static_cast<T&&>(t);
}

}  // namespace mge::utility
