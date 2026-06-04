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
 * @file compiler.hpp
 * @brief Detects which compiler is currently running.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/** @brief Tag for MSVC Compiler. */
#define MGE_COMPILER_MSVC 0
/** @brief Tag for Clang Compiler. */
#define MGE_COMPILER_CLANG 0
/** @brief Tag for GCC Compiler. */
#define MGE_COMPILER_GCC 0

/** @brief Detects the current compiler. */
#if defined(_MSC_VER)
#  undef MGE_COMPILER_MSVC
#  define MGE_COMPILER_MSVC 1
#  define MGE_COMPILER "MSVC"
#elif defined(__clang__)
#  undef MGE_COMPILER_CLANG
#  define MGE_COMPILER_CLANG 1
#  define MGE_COMPILER "CLANG"
#elif defined(__GNUC__) || defined(__GNUG__)
#  undef MGE_COMPILER_GCC
#  define MGE_COMPILER_GCC 1
#  define MGE_COMPILER "GCC"
#else
#  error "[MGE] - Core - Unsupported compiler."
#endif
