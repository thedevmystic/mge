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
 * @file architecture.hpp
 * @brief Detects which architecture (CPU) is currently running.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/** @brief Tag for X64. */
#define MGE_ARCHITECTURE_X64 0
/** @brief Tag for ARM64. */
#define MGE_ARCHITECTURE_ARM 0

/** @brief Detects the current architecture. */
#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#  undef MGE_ARCHITECTURE_X64
#  define MGE_ARCHITECTURE_X64 1
#  define MGE_ARCHITECTURE "X64"
#elif defined(__aarch64__) || defined(_M_ARM64) || defined(__arm64__)
#  undef MGE_ARCHITECTURE_ARM
#  define MGE_ARCHITECTURE_ARM 1
#  define MGE_ARCHITECTURE "ARM64"
#else
#  error "[MGE] - Core - Unsupported architecture."
#endif
