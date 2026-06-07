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
 * @file platform.hpp
 * @brief Detects which platform (OS) is currently running.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/**
 * @addtogroup hal
 * @{
 */

/** @brief Tag for Windows. */
#define MGE_PLATFORM_WINDOWS 0
/** @brief Tag for Linux. */
#define MGE_PLATFORM_LINUX 0
/** @brief Tag for MacOS. */
#define MGE_PLATFORM_MACOS 0

/** @brief Detects the current platform. */
#if defined(_WIN32) || defined(_WIN64)
#  undef MGE_PLATFORM_WINDOWS
#  define MGE_PLATFORM_WINDOWS 1
#  define MGE_PLATFORM "WINDOWS"
#elif defined(__linux__) || defined(__gnu_linux__)
#  undef MGE_PLATFORM_LINUX
#  define MGE_PLATFORM_LINUX 1
#  define MGE_PLATFORM "LINUX"
#elif defined(__APPLE__) || defined(__MACH__)
#  error "[MGE] - Core - MacOS is currently not supported."
#else
#  error "[MGE] - Core - Unsupported platform."
#endif

/** @} */ // addtogroup hal
