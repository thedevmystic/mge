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
 * @file byte.hpp
 * @brief Defines byte type.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "common/attributes.hpp"
#include "common/types.hpp"

namespace mge {
inline namespace types {

/**
 * @addtogroup common
 * @{
 */

/** @brief Byte type. */
enum class MGE_API Byte : uint8 {};

/* =============================================================================================
    Bitwise Operators
   --------------------------------------------------------------------------------------------- */
/** @brief Bitwise AND operator. */
MGE_FORCEINLINE constexpr Byte operator&(const Byte lhs, const Byte rhs) {
  return static_cast<Byte>(static_cast<uint8>(lhs) & static_cast<uint8>(rhs));
}

/** @brief Bitwise OR operator. */
MGE_FORCEINLINE constexpr Byte operator|(const Byte lhs, const Byte rhs) {
  return static_cast<Byte>(static_cast<uint8>(lhs) | static_cast<uint8>(rhs));
}

/** @brief Bitwise XOR operator. */
MGE_FORCEINLINE constexpr Byte operator^(const Byte lhs, const Byte rhs) {
  return static_cast<Byte>(static_cast<uint8>(lhs) ^ static_cast<uint8>(rhs));
}

/** @brief Bitwise NOT operator. */
MGE_FORCEINLINE constexpr Byte operator~(const Byte b) {
  return static_cast<Byte>(~static_cast<uint8>(b));
}

/** @brief Bitwise left shift operator. */
MGE_FORCEINLINE constexpr Byte operator<<(const Byte b, const int shift) {
  return static_cast<Byte>(static_cast<uint8>(b) << shift);
}

/** @brief Bitwise right operator. */
MGE_FORCEINLINE constexpr Byte operator>>(const Byte b, const int shift) {
  return static_cast<Byte>(static_cast<uint8>(b) >> shift);
}

/* =============================================================================================
    Bitwise Compound Operators
   --------------------------------------------------------------------------------------------- */
/** @brief Bitwise compound AND operator. */
MGE_FORCEINLINE constexpr Byte& operator&=(Byte& lhs, const Byte rhs) {
  lhs = lhs & rhs;
  return lhs;
}

/** @brief Bitwise compound OR operator. */
MGE_FORCEINLINE constexpr Byte& operator|=(Byte& lhs, const Byte rhs) {
  lhs = lhs | rhs;
  return lhs;
}

/** @brief Bitwise compound XOR operator. */
MGE_FORCEINLINE constexpr Byte& operator^=(Byte& lhs, const Byte rhs) {
  lhs = lhs ^ rhs;
  return lhs;
}

/** @brief Bitwise compound left shift operator. */
MGE_FORCEINLINE constexpr Byte& operator<<=(Byte& b, const int shift) {
  b = b << shift;
  return b;
}

/** @brief Bitwise compound right operator. */
MGE_FORCEINLINE constexpr Byte& operator>>=(Byte& b, const int shift) {
  b = b >> shift;
  return b;
}

/** @} */  // addtogroup common

}  // namespace types
}  // namespace mge
