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
 * @file platform_types.hpp
 * @brief Defines unified types across platforms.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * @note Only targets 64-bit architecture.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "hal/compiler.hpp"

/** @brief Defines unified intN types. */
#if MGE_COMPILER_GCC || MGE_COMPILER_CLANG
#  define MGE_PLATFORM_INT8 __INT8_TYPE__
#  define MGE_PLATFORM_INT16 __INT16_TYPE__
#  define MGE_PLATFORM_INT32 __INT32_TYPE__
#  define MGE_PLATFORM_INT64 __INT64_TYPE__
#elif MGE_COMPILER_MSVC
#  define MGE_PLATFORM_INT8 __int8
#  define MGE_PLATFORM_INT16 __int16
#  define MGE_PLATFORM_INT32 __int32
#  define MGE_PLATFORM_INT64 __int64
#endif

/** @brief Defines unified uintN types. */
#if MGE_COMPILER_GCC || MGE_COMPILER_CLANG
#  define MGE_PLATFORM_UINT8 __UINT8_TYPE__
#  define MGE_PLATFORM_UINT16 __UINT16_TYPE__
#  define MGE_PLATFORM_UINT32 __UINT32_TYPE__
#  define MGE_PLATFORM_UINT64 __UINT64_TYPE__
#elif MGE_COMPILER_MSVC
#  define MGE_PLATFORM_UINT8 unsigned __int8
#  define MGE_PLATFORM_UINT16 unsigned __int16
#  define MGE_PLATFORM_UINT32 unsigned __int32
#  define MGE_PLATFORM_UINT64 unsigned __int64
#endif

/** @brief Defines unified intptr, uintptr, ptrdiff, and size types. */
#if MGE_COMPILER_GCC || MGE_COMPILER_CLANG
#  define MGE_PLATFORM_INTPTR __INTPTR_TYPE__
#  define MGE_PLATFORM_UINTPTR __UINTPTR_TYPE__
#  define MGE_PLATFORM_PTRDIFF __PTRDIFF_TYPE__
#  define MGE_PLATFORM_SIZET __SIZE_TYPE__
#elif MGE_COMPILER_MSVC
#  define MGE_PLATFORM_INTPTR __int64
#  define MGE_PLATFORM_UINTPTR unsigned __int64
#  define MGE_PLATFORM_PTRDIFF __int64
#  define MGE_PLATFORM_SIZET unsigned __int64
#endif

/** @brief Defines nullptr type. */
#define MGE_PLATFORM_NULL_TYPE decltype(nullptr)
