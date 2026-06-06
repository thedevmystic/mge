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
 * @file attributes.hpp
 * @brief Defines core attributes if present, no-op otherwise.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * @note Baseline is C++20.
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

/** @brief Checks if C++ attribute is supported or not. */
#if defined(__has_cpp_attribute)
#  define MGE_HAS_ATTRIBUTE(attr) __has_cpp_attribute(attr)
#else
#  define MGE_HAS_ATTRIBUTE(attr) 0  ///< 0 as we can not determine
#endif

/** @brief Checks if builtin is supported or not. */
#if defined(__has_builtin)
#  define MGE_HAS_BUILTIN(expr) __has_builtin(expr)
#else
#  define MGE_HAS_BUILTIN(expr) 0  ///< 0 as we can not determine
#endif

/** @brief Checks if feature is supported or not. */
#if defined(__has_feature)
#  define MGE_HAS_FEATURE(feat) __has_feature(feat)
#else
#  define MGE_HAS_FEATURE(feat) 0  ///< 0 as we can not determine
#endif

/** @brief Checks if include is supported or not. */
#if defined(__has_include)
#  define MGE_HAS_INCLUDE(inc) __has_include(inc)
#else
#  define MGE_HAS_INCLUDE(inc) 0  ///< 0 as we can not determine
#endif

/* ========================================
    Standard C++ Attributes
   ---------------------------------------- */
/** @brief Noreturn attribute, meaning that this function never returns to the caller. */
#if MGE_HAS_ATTRIBUTE(noreturn)
#  define MGE_NORETURN [[noreturn]]
#else
#  define MGE_NORETURN
#endif

/** @brief Deprecated attribute, marking the old API for deprecation. */
#if MGE_HAS_ATTRIBUTE(deprecated)
#  define MGE_DEPRECATED [[deprecated]]
#  define MGE_DEPRECATED_MSG(msg) [[deprecated(msg)]]
#else
#  define MGE_DEPRECATED
#  define MGE_DEPRECATED_MSG(msg)
#endif

/** @brief Fallthrough attribute, marking intentional missing break statement. */
#if MGE_HAS_ATTRIBUTE(fallthrough)
#  define MGE_FALLTHROUGH [[fallthrough]]
#else
#  define MGE_FALLTHROUGH
#endif

/** @brief Unused attribute, marking that a variable maybe unused. */
#if MGE_HAS_ATTRIBUTE(maybe_unused)
#  define MGE_UNUSED [[maybe_unused]]
#else
#  define MGE_UNUSED
#endif

/** @brief Nodisacrd attribute, meaning the resulting value should not be ignored. */
#if MGE_HAS_ATTRIBUTE(nodiscard)
#  define MGE_NODISCARD [[nodiscard]]
#  define MGE_NODISCARD_MSG(msg) [[nodiscard(msg)]]
#else
#  define MGE_NODISCARD
#  define MGE_NODISCARD_MSG(msg)
#endif

/** @brief Likely and unlikely attributes, used for branch prediction. */
#if MGE_HAS_ATTRIBUTE(likely) && MGE_HAS_ATTRIBUTE(unlikely)
#  define MGE_LIKELY [[likely]]
#  define MGE_UNLIKELY [[unlikely]]
#else
#  define MGE_LIKELY
#  define MGE_UNLIKELY
#endif

/** @brief No unique address attribute, disables standard alignment padding. */
#if MGE_HAS_ATTRIBUTE(msvc::no_unique_address)
// MSVC does not support standard attribute.
#  define MGE_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#elif MGE_HAS_ATTRIBUTE(no_unique_address)
#  define MGE_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#  define MGE_NO_UNIQUE_ADDRESS
#endif

/** @brief Assume attribute, assume the expr something is true. */
#if MGE_HAS_ATTRIBUTE(assume) >= 202207L
#  define MGE_ASSUME(expr) [[assume(expr)]]
#elif MGE_COMPILER_MSVC
#  define MGE_ASSUME(expr) __assume(expr)
#elif MGE_COMPILER_CLANG
#  define MGE_ASSUME(expr) __builtin_assume(expr)
#elif MGE_COMPILER_GCC
#  define MGE_ASSUME(expr) (!!(expr) ? static_cast<void>(0) : __builtin_unreachable())
#else
#  define MGE_ASSUME(expr)
#endif

/** @brief Alias for unreachable code. */
#define MGE_UNREACHABLE MGE_ASSUME(0)

/* ========================================
    Vendor Attributes
   ---------------------------------------- */
/** @brief Forceinline, gives a stronger hint to inline a function. */
#if MGE_COMPILER_MSVC
#  define MGE_FORCEINLINE __forceinline inline
#elif MGE_COMPILER_CLANG
#  define MGE_FORCEINLINE __attribute__((always_inline)) inline
#elif MGE_COMPILER_GCC
#  define MGE_FORCEINLINE __attribute__((always_inline)) inline
#else
#  define MGE_FORCEINLINE inline
#endif

/** @brief Noinline, prevents a function inlining. */
#if MGE_COMPILER_MSVC
#  define MGE_NOINLINE __declspec(noinline)
#elif MGE_COMPILER_CLANG || MGE_COMPILER_GCC
#  define MGE_NOINLINE __attribute__((noinline))
#else
#  define MGE_NOINLINE
#endif

/** @brief Returns non-null value. */
#if MGE_COMPILER_MSVC
#  include <sal.h>
#  define MGE_RETURNS_NONNULL _Ret_notnull_
#elif MGE_COMPILER_CLANG || MGE_COMPILER_GCC
#  define MGE_RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#  define MGE_RETURNS_NONNULL
#endif

/**
 * @brief Should be a non-null value. Supported by Clang.
 *
 * Nonnull pointers should never be null. It is the responsibility of the provider to ensure that
 * the value of this pointer is never set to a null value (NULL or nullptr).
 *
 * @code
 * // A const non-null pointer to Base:
 * Base* MGE_NONNULL const ptr;
 *
 * // A non-null pointer to const Base:
 * const Base* MGE_NONNULL ptr;
 *
 * // A const non-null pointer to const Base:
 * const Base* MGE_NONNULL const ptr;
 *
 * // A non-null pointer to a const non-null pointer to Base:
 * Base* MGE_NONNULL const* MGE_NONNULL ptr;
 *
 * // A non-null function pointer:
 * void (*MGE_NONNULL func)(int, double);
 *
 * // A non-null array of Base as parameter:
 * void func(Base bases[MGE_NONNULL]);
 *
 * // With std::unique_ptr
 * MGE_NONNULL std::unique_ptr<Base> base;
 * std::unique_ptr<Base> MGE_NONNULL base; // this also works.
 * @endcode
 *
 * @note This is primary for human readability and does not provide any guarantees about the type
 * itself.
 */
#if MGE_COMPILER_CLANG
#  define MGE_NONNULL _Nonnull
#else
#  define MGE_NONNULL
#endif

/**
 * @brief Should be a null value. Supported by Clang.
 *
 * Nullable pointers may or may not be null. The consumer should be responsible to check the
 * the value of this pointer is not null.
 *
 * @code
 * // Similar to MGE_NONNULL
 *
 * // Invalid Usage:
 * MGE_NULLABLE Base* base; // tries to define a nullable pointer to base, which is meaningless.
 * @endcode
 *
 * @note This is primary for human readability and does not provide any guarantees about the type
 * itself.
 */
#if MGE_COMPILER_CLANG
#  define MGE_NULLABLE _Nullable
#else
#  define MGE_NULLABLE
#endif

/**
 * @brief Marks a class compatible with Nullability annotation.
 *
 * @code
 * struct MGE_NULLABILITY_COMPATIBLE SuperCool9000 {
 *   ...
 * };
 * @endcode
 *
 * @note This is primary for human readability and does not provide any guarantees about the type
 * itself.
 */
#if MGE_COMPILER_CLANG && MGE_HAS_FEATURE(nullability_on_classes)
#  define MGE_NULLABILITY_COMPATIBLE _Nullable
#else
#  define MGE_NULLABILITY_COMPATIBLE
#endif

/**
 * @brief Trivial ABI marker.
 *
 * @code
 * struct MGE_TRIVIAL_ABI SuperCool9000 {
 *   ...
 * };
 * @endcode
 */
#if (MGE_COMPILER_CLANG) || (MGE_COMPILER_GCC)
#  define MGE_TRIVIAL_ABI [[clang::trivial_abi]]
#else
#  define MGE_TRIVIAL_ABI
#endif

/** @} */  // end of addtogroup common
