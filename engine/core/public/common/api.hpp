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
 * @file api.hpp
 * @brief Defines API macro.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "hal/compiler.hpp"

/**
 * @addtogroup common
 * @{
 */

/**
 * @brief API visibility marker.
 *
 * @code
 * // For classes / structs
 * struct MGE_API SuperCool9000 {
 *   ...
 * };
 *
 * // For functions
 * MGE_API void super();
 * @endcode
 *
 * @note Function has to be marked with it only once (prefer in header).
 */
#if MGE_COMPILER_MSVC
#  if defined(MGE_EXPORT_SYMBOLS)
#    define MGE_API __declspec(dllexport)
#  else
#    define MGE_API __declspec(dllimport)
#  endif
#elif MGE_COMPILER_CLANG || MGE_COMPILER_GCC
#  if defined(MGE_EXPORT_SYMBOLS)
#    define MGE_API __attribute__((visibility("default")))
#  else
#    define MGE_API
#  endif
#else
#  define MGE_API
#endif

/** @} */  // end of addtogroup common
