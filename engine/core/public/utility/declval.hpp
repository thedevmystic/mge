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
 * @brief Defines declval utility helper to produce rvalue reference in unevaluated contexts.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "traits/reference_transformations.hpp"

namespace mge::utility {

/**
 * @brief Decval utility helper to produce rvalue references in unevaluated contexts (i.e., sizeof,
 *        decltype, noexcept).
 * @tparam T Type of the object.
 * @returns Rvalue reference of the the object `(T)`.
 * @ingroup utility
 */
template <typename T>
typename ::mge::traits::add_rvalue_reference<T>::type declval() noexcept;

} // namespace mge::utility
