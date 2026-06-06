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
 * @file types.hpp
 * @brief Defines unified types across using HAL.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "hal/platform_types.hpp"

namespace mge {
inline namespace types {

/**
 * @addtogroup common
 * @{
 */

/** @brief int types. */
using int8 = MGE_PLATFORM_INT8;
using int16 = MGE_PLATFORM_INT16;
using int32 = MGE_PLATFORM_INT32;
using int64 = MGE_PLATFORM_INT64;

/** @brief uint types. */
using uint8 = MGE_PLATFORM_UINT8;
using uint16 = MGE_PLATFORM_UINT16;
using uint32 = MGE_PLATFORM_UINT32;
using uint64 = MGE_PLATFORM_UINT64;

/** @brief intptr, uintptr, ptrdiff, and usize types. */
using intptr = MGE_PLATFORM_INTPTR;
using uintptr = MGE_PLATFORM_UINTPTR;
using ptrdiff = MGE_PLATFORM_PTRDIFF;
using usize = MGE_PLATFORM_SIZET;

/** @brief Null type. */
using null_type = MGE_PLATFORM_NULL_TYPE;

/** @brief Exit codes. */
inline constexpr int8 EXIT_CODE_SUCCESS = 0;
inline constexpr int8 EXIT_CODE_FAILURE = 1;

/** @} */  // addtogroup common

}  // namespace types
}  // namespace mge
