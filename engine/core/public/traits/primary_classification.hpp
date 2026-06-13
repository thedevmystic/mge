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
 * @file primary_classification.hpp
 * @brief Consolidated type traits for primary classification of any type.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following identity and classification traits:
 * - `is_void` / `is_void_v`                 : Checks if a given type represents a void type.
 * - `is_null_pointer` / `is_null_pointer_v`   : Checks if a given type represents a nullptr type.
 * - `is_integral` / `is_integral_v`         : Checks if a given type represents a integral type.
 * - `is_floating_point` / `is_floating_point_v` : Checks if a given type represents a fp type.
 * - `is_array` / `is_array_v`               : Checks if a given type represents a raw C-style
 *                                             array.
 * - `is_pointer` / `is_pointer_v`           : Checks if a given type represents a pointer type.
 * - `is_lvalue_reference` / `is_lvalue_reference_v` : Checks if a given type is an lvalue
 *                                                     reference.
 * - `is_rvalue_reference` / `is_rvalue_reference_v` : Checks if a given type is an rvalue
 *                                                     reference.
 * - `is_enum` / `is_enum_v`                 : Checks if a given type represents a enum type.
 * - `is_class` / `is_class_v`               : Checks if a given type represents a class type.
 * - `is_union` / `is_union_v`               : Checks if a given type represents a union type.
 * - `is_function` / `is_function_v`         : Checks if a given type represents a function type.
 * - `is_member_function_pointer` \
 *   `is_member_function_pointer_v`  : Checks if a given type represents a member function pointer.
 * - `is_member_object_pointer` \
 *   `is_member_object_pointer_v`    : Checks if a given type represents a member object pointer.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "common/types.hpp"
#include "traits/core.hpp"

// #region Detail
namespace mge::traits::detail {

// #region Local Remove CV-Qualifiers
namespace primary_classification {
template <typename T>
struct local_remove_cv {
  using type = T;
};
template <typename T>
struct local_remove_cv<const T> {
  using type = T;
};
template <typename T>
struct local_remove_cv<volatile T> {
  using type = T;
};
template <typename T>
struct local_remove_cv<const volatile T> {
  using type = T;
};
}  // namespace primary_classification
// #endregion

// #region Void Type Trait Helper
/** @brief is_void sub helper. */
template <typename T>
struct is_void_sub_helper : false_type {};

/** @brief Initialize for void types. */
template <>
struct is_void_sub_helper<void> : true_type {};

/** @brief is_void helper. */
template <typename T>
struct is_void_helper
    : is_void_sub_helper<typename primary_classification::local_remove_cv<T>::type> {};
// #endregion

// #region Null Pointer Type Trait Helper
/** @brief is_null_pointer sub helper. */
template <typename T>
struct is_null_pointer_sub_helper : false_type {};

/** @brief Initialize for nullptr types. */
template <>
struct is_null_pointer_sub_helper<null_type> : true_type {};

/** @brief is_null_pointer helper. */
template <typename T>
struct is_null_pointer_helper
    : is_null_pointer_sub_helper<typename primary_classification::local_remove_cv<T>::type> {};
// #endregion

// #region Integral Type Trait Helper
/** @brief is_integral sub helper. */
template <typename T>
struct is_integral_sub_helper : false_type {};

/** @brief If integral type, then true type. */
template <>
struct is_integral_sub_helper<bool> : true_type {};
template <>
struct is_integral_sub_helper<char> : true_type {};
template <>
struct is_integral_sub_helper<signed char> : true_type {};
template <>
struct is_integral_sub_helper<unsigned char> : true_type {};
template <>
struct is_integral_sub_helper<wchar_t> : true_type {};
template <>
struct is_integral_sub_helper<char8_t> : true_type {};
template <>
struct is_integral_sub_helper<char16_t> : true_type {};
template <>
struct is_integral_sub_helper<char32_t> : true_type {};
template <>
struct is_integral_sub_helper<short> : true_type {};
template <>
struct is_integral_sub_helper<unsigned short> : true_type {};
template <>
struct is_integral_sub_helper<int> : true_type {};
template <>
struct is_integral_sub_helper<unsigned int> : true_type {};
template <>
struct is_integral_sub_helper<long> : true_type {};
template <>
struct is_integral_sub_helper<unsigned long> : true_type {};
template <>
struct is_integral_sub_helper<long long> : true_type {};
template <>
struct is_integral_sub_helper<unsigned long long> : true_type {};

/** @brief is_integral helper. */
template <typename T>
struct is_integral_helper
    : is_integral_sub_helper<typename primary_classification::local_remove_cv<T>::type> {};
// #endregion

// #region Floating Point Type Trait Helper
/** @brief is_floating_point sub helper. */
template <typename T>
struct is_floating_point_sub_helper : false_type {};

/** @brief If floating point type, then true type. */
template <>
struct is_floating_point_sub_helper<float> : true_type {};
template <>
struct is_floating_point_sub_helper<double> : true_type {};
template <>
struct is_floating_point_sub_helper<long double> : true_type {};

/** @brief is_floating_point helper. */
template <typename T>
struct is_floating_point_helper
    : is_floating_point_sub_helper<typename primary_classification::local_remove_cv<T>::type> {};
// #endregion

// #region Array Type Trait Helper
/** @brief is_array helper. */
template <typename T>
struct is_array_helper : false_type {};

/** @brief If array, then true type. */
template <typename T>
struct is_array_helper<T[]> : true_type {};

template <typename T, unsigned N>
struct is_array_helper<T[N]> : true_type {};
// #endregion

// #region Pointer Type Trait Helper
/** @brief is_pointer sub helper. */
template <typename T>
struct is_pointer_sub_helper : false_type {};

/** @brief Initialize for pointer types. */
template <typename T>
struct is_pointer_sub_helper<T*> : true_type {};

/** @brief is_pointer helper. */
template <typename T>
struct is_pointer_helper
    : is_pointer_sub_helper<typename primary_classification::local_remove_cv<T>::type> {};
// #endregion

// #region Lvalue Reference Type Traits Helper
/** @brief is_lvalue_reference helper. */
template <typename T>
struct is_lvalue_reference_helper : false_type {};

/** @brief If lvalue, then true type. */
template <typename T>
struct is_lvalue_reference_helper<T&> : true_type {};
// #endregion

// #region Rvalue Reference Type Traits Helper
/** @brief is_rvalue_reference helper. */
template <typename T>
struct is_rvalue_reference_helper : false_type {};

/** @brief If rvalue, then true type. */
template <typename T>
struct is_rvalue_reference_helper<T&&> : true_type {};
// #endregion

// #region Enum Type Trait Helper
/** @brief is_enum helper. */
template <typename T>
struct is_enum_helper : integral_constant<bool, __is_enum(T)> {};
// #endregion

// #region Class Type Trait Helper
/** @brief is_class helper. */
template <typename T>
struct is_class_helper : integral_constant<bool, __is_class(T)> {};
// #endregion

// #region Union Type Trait Helper
/** @brief is_union helper. */
template <typename T>
struct is_union_helper : integral_constant<bool, __is_union(T)> {};
// #endregion

// #region Function Type Trait Helper
namespace is_func_impl {
struct size_one {
  char tag;
};
struct size_two {
  char tag[2];
};
struct Dummy {};
template <typename T>
size_one test(T*);
template <typename T>
size_one test(Dummy);
template <typename T>
size_two test(...);
template <typename T>
T& source(int);
template <typename T>
Dummy source(...);
}  // namespace is_func_impl

/** @brief is_function helper. */
template <typename T, bool = is_class_helper<T>::value || is_union_helper<T>::value ||
                             is_void_helper<T>::value || is_lvalue_reference_helper<T>::value ||
                             is_rvalue_reference_helper<T>::value ||
                             is_null_pointer_helper<T>::value>
struct is_function_helper
    : integral_constant<bool, sizeof(is_func_impl::test<T>(is_func_impl::source<T>(0))) == 1> {};
template <typename T>
struct is_function_helper<T, true> : false_type {};
// #endregion

// #region Member Function Pointer Type Trait Helper
/** @brief is_member_function_pointer sub helper. */
template <typename T>
struct is_member_function_pointer_sub_helper : false_type {};

/** @brief Initialize for member function pointer types. */
template <typename T, typename U>
struct is_member_function_pointer_sub_helper<T U::*> : is_function_helper<T> {};

/** @brief is_member_function_pointer helper. */
template <typename T>
struct is_member_function_pointer_helper
    : is_member_function_pointer_sub_helper<
          typename primary_classification::local_remove_cv<T>::type> {};
// #endregion

// #region Member Object Pointer Type Trait Helper
/** @brief is_member_object_pointer helper. */
template <typename T>
struct is_member_object_pointer_sub_helper : false_type {};

/** @brief Initialize for member object pointer types. */
// If A is a member pointer (T U::*) but not a member_function_pointer, then it must be an obj ptr.
template <typename T, typename U>
struct is_member_object_pointer_sub_helper<T U::*>
    : integral_constant<bool, !is_member_function_pointer_helper<T U::*>::value> {};

/** @brief is_member_object_pointer helper. */
template <typename T>
struct is_member_object_pointer_helper
    : is_member_object_pointer_sub_helper<
          typename primary_classification::local_remove_cv<T>::type> {};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

// #region Primary Classification Trait - Void
/**
 * @brief A type used to check if an object is void.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_void : detail::is_void_helper<T> {};

/**
 * @brief Value alias for is_void.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_void_v = is_void<T>::value;
// #endregion

// #region Primary Classification Trait - Null Pointer
/**
 * @brief A type used to check if an object is null pointer.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_null_pointer : detail::is_null_pointer_helper<T> {};

/**
 * @brief Value alias for is_null_pointer.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;
// #endregion

// #region Primary Classification Trait - Integral
/**
 * @brief A type used to check if an object is integral.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_integral : detail::is_integral_helper<T> {};

/**
 * @brief Value alias for is_integral.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_integral_v = is_integral<T>::value;
// #endregion

// #region Primary Classification Trait - Floating Point
/*
 * @brief A type used to check if an object is floating point.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_floating_point : detail::is_floating_point_helper<T> {};

/**
 * @brief Value alias for is_floating_point.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;
// #endregion

// #region Primary Classification Trait - Array
/**
 * @brief A type used to check if an object is array.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_array : detail::is_array_helper<T> {};

/**
 * @brief Value alias for is_array.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_array_v = is_array<T>::value;
// #endregion

// #region Primary Classification Trait - Pointer
/**
 * @brief A type used to check if an object is pointer.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_pointer : detail::is_pointer_helper<T> {};

/**
 * @brief Value alias for is_pointer.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_pointer_v = is_pointer<T>::value;
// #endregion

// #region Primary Classification Trait - Lvalue Reference
/**
 * @brief A type used to check if an object is lvalue reference.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_lvalue_reference : detail::is_lvalue_reference_helper<T> {};

/**
 * @brief Value alias for is_lvalue_reference.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
// #endregion

// #region Primary Classification Trait - Rvalue Reference
/**
 * @brief A type used to check if an object is rvalue reference.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_rvalue_reference : detail::is_rvalue_reference_helper<T> {};

/**
 * @brief Value alias for is_rvalue_reference.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
// #endregion

// #region Primary Classification Trait - Enum
/**
 * @brief A type used to check if an object is enum.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_enum : detail::is_enum_helper<T> {};

/**
 * @brief Value alias for is_enum.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_enum_v = is_enum<T>::value;
// #endregion

// #region Primary Classification Trait - Class
/**
 * @brief A type used to check if an object is class.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_class : detail::is_class_helper<T> {};

/**
 * @brief Value alias for is_class.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_class_v = is_class<T>::value;
// #endregion

// #region Primary Classification Trait - Union
/**
 * @brief A type used to check if an object is union.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_union : detail::is_union_helper<T> {};

/**
 * @brief Value alias for is_union.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_union_v = is_union<T>::value;
// #endregion

// #region Primary Classification Trait - Function
/**
 * @brief A type used to check if an object is function.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_function : detail::is_function_helper<T> {};

/**
 * @brief Value alias for is_function.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_function_v = is_function<T>::value;
// #endregion

// #region Primary Classification Trait - Member Function Pointer
/**
 * @brief A type used to check if an object is member function pointer.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_member_function_pointer : detail::is_member_function_pointer_helper<T> {
};

/**
 * @brief Value alias for is_member_function_pointer.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;
// #endregion

// #region Primary Classification Trait - Member Object Pointer
/**
 * @brief A type used to check if an object is member object pointer.
 * @tparam T Type of the object.
 * @ingroup traits
 */
template <typename T>
struct MGE_API_TEMPLATE is_member_object_pointer : detail::is_member_object_pointer_helper<T> {};

/**
 * @brief Value alias for is_member_object_pointer.
 * @ingroup traits
 */
template <typename T>
inline constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;
// #endregion

}  // namespace mge::traits
// #endregion
