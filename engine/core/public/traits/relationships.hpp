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
 * @file relationships.hpp
 * @brief Consolidated type traits for relationship determination between two types.
 * @author thedevmystic (Surya) <thedevmystic@gmail.com>
 *
 * This header provides the following relationship traits:
 * - `is_same` / `is_same_v`               : Checks if two types are the same type.
 * - `is_convertible` / `is_convertible_v` : Checks if a type is convertible to other type.
 * - `is_nothrow_convertible` /
 *   `is_nothrow_convertible_v`            : Checks if a type is nothrow convertible to other type.
 * - `is_base_of` / `is_base_of_v`         : Checks if a type is base of the other type.
 * - `is_virtual_base_of` /
 *   `is_virtual_base_of_v`                : Checks if a type is virtual base of the other type.
 * - `is_invocable` / `is_invocable_v`     : Checks if a type is invocable.
 * - `is_invocable_r` / `is_invocable_r_v` : Checks if a type is invocable with a specific return.
 * - `is_nothrow_invocable` /
 *   `is_nothrow_invocable_v`     : Checks if a type is nothrow invocable.
 * - `is_nothrow_invocable_r` /
 *   `is_nothrow_invocable_r_v`   : Checks if a type is nothrow invocable with a specific return.
 *
 * SPDX-FileCopyrightText: 2026-present Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "common/api.hpp"
#include "hal/compiler.hpp"
#include "traits/array_traits.hpp"
#include "traits/core.hpp"
#include "traits/cv_traits.hpp"
#include "traits/member_introspection.hpp"
#include "traits/pointer_transformations.hpp"
#include "traits/primary_classification.hpp"
#include "traits/reference_transformations.hpp"
#include "utility/declval.hpp"
#include "utility/forward.hpp"

// #region Forward Dec
namespace mge::utility {
template <typename T>
struct reference_wrapper;
}
// #endregion

// #region Detail
namespace mge::traits::detail {

// #region Same Type Trait Helper
/** @brief is_same helper. */
template <typename T, typename U>
struct is_same_helper : false_type {};

/** @brief If both are same type, then true. */
template <typename T>
struct is_same_helper<T, T> : true_type {};
// #endregion

// #region Convertible Type Trait Helper
/** @brief is_convertible helper. */
template <typename T, typename U>
#if MGE_COMPILER_GCC
struct is_convertible_helper
    : integral_constant<bool, !is_abstract_v<U> && __is_convertible(T, U)> {
};
#else
struct is_convertible_helper
    : integral_constant<bool, !is_abstract_v<U> && __is_convertible_to(T, U)> {
};
#endif
// #endregion

// #region Nothrow Convertible Type Trait Helper
namespace is_nothrow_convertible_impl {
template <typename U>
void test(U) noexcept;

template <typename T, typename U, bool = is_convertible_helper<T, U>::value && !is_abstract_v<U>>
struct check : false_type {};

template <typename T, typename U>
struct check<T, U, true> : bool_constant<noexcept(test<U>(::mge::utility::declval<T>()))> {};
}  // namespace is_nothrow_convertible_impl

/** @brief is_nothrow_convertible helper. */
template <typename T, typename U>
struct is_nothrow_convertible_helper : is_nothrow_convertible_impl::check<T, U> {};
// #endregion

// #region Base Of Type Trait Helper
/** @brief is_base_of helper. */
template <typename B, typename D>
struct is_base_of_helper : integral_constant<bool, __is_base_of(B, D)> {};
// #endregion

// #region Virtual Base Of Type Trait Helper
namespace is_virtual_base_of_impl {
struct size_one {
  char tag;
};
struct size_two {
  char tag[2];
};
template <typename T, int N>
struct wrap : T {};
template <typename B, typename D>
struct double_derived : wrap<D, 0>, wrap<D, 1> {};
template <typename B, typename D>
size_one test(int, enable_if_t<is_convertible_helper<double_derived<B, D>*, B*>::value,
                               double_derived<B, D>>* = nullptr);
template <typename B, typename D>
size_two test(...);
}  // namespace is_virtual_base_of_impl

/** @brief is_virtual_base_of helper. */
template <typename B, typename D>
struct is_virtual_base_of_helper
    : integral_constant<bool, is_base_of_helper<B, D>::value &&
                                  sizeof(is_virtual_base_of_impl::test<B, D>(0, nullptr)) != 2> {};
// #endregion

// #region Invocable Trait Helper
namespace invoke_impl {
template <typename...>
using local_void_t = void;

/** Local impl of decay to avoid cir. dep. */
template <class U, bool>
struct local_decay_helper {
  using type = remove_cv_t<U>;
};

template <class U>
struct local_decay_helper<U, true> {
 public:
  using type = conditional_t<is_array_v<U>, remove_extent_t<U>*,
                             conditional_t<is_function_v<U>, add_pointer_t<U>, remove_cv_t<U>>>;
};

template <class T>
struct local_decay {
 private:
  using U = remove_reference_t<T>;

 public:
  using type =
      typename local_decay_helper<U, reference_transformations::is_referenceable<U>::value>::type;
};

template <class T>
using local_decay_t = typename local_decay<T>::type;

/** type trait to detect reference wrapper. */
template <typename T>
struct is_reference_wrapper : false_type {};

template <typename T>
struct is_reference_wrapper<::mge::utility::reference_wrapper<T>> : true_type {};

template <typename T>
inline constexpr bool is_reference_wrapper_v = is_reference_wrapper<T>::value;

/** member_class to extract owning class from pointer-to-member. */
template <typename T, typename = void>
struct member_class;

#define MGE_INTERNAL_MEMFN_CLASS(CV, REF, NOEX)     \
  template <typename R, typename C, typename... A>  \
  struct member_class<R (C::*)(A...) CV REF NOEX> { \
    using type = C;                                 \
  };

#define MGE_INTERNAL_MEMFN_NOEX(CV, REF) \
  MGE_INTERNAL_MEMFN_CLASS(CV, REF, )    \
  MGE_INTERNAL_MEMFN_CLASS(CV, REF, noexcept)

#define MGE_INTERNAL_MEMFN_REF(CV) \
  MGE_INTERNAL_MEMFN_NOEX(CV, ) MGE_INTERNAL_MEMFN_NOEX(CV, &) MGE_INTERNAL_MEMFN_NOEX(CV, &&)

MGE_INTERNAL_MEMFN_REF()
MGE_INTERNAL_MEMFN_REF(const)
MGE_INTERNAL_MEMFN_REF(volatile)
MGE_INTERNAL_MEMFN_REF(const volatile)

#undef MGE_INTERNAL_MEMFN_CLASS
#undef MGE_INTERNAL_MEMFN_NOEX
#undef MGE_INTERNAL_MEMFN_REF

/** member object pointer. */
template <typename R, typename C>
struct member_class<R C::*> {
  using type = C;
};

template <typename T>
using member_class_t = typename member_class<local_decay_t<T>>::type;

/** predicate helpers. */
template <typename F>
using is_memfn = is_member_function_pointer<local_decay_t<F>>;

template <typename F>
using is_memobj = is_member_object_pointer<local_decay_t<F>>;

template <typename F, typename T, bool IsMem>
struct is_base_match_helper : false_type {};
template <typename F, typename T>
struct is_base_match_helper<F, T, true>
    : integral_constant<
          bool, is_base_of_helper<member_class_t<local_decay_t<F>>, local_decay_t<T>>::value> {};
template <typename F, typename T>
struct is_base_match : is_base_match_helper<F, T, (is_memfn<F>::value || is_memobj<F>::value)> {};

/** tag types for six invoke cases. */
struct tag_memfn_base {};
struct tag_memfn_wrap {};
struct tag_memfn_ptr {};
struct tag_memobj_base {};
struct tag_memobj_wrap {};
struct tag_memobj_ptr {};
struct tag_other {};

/** tag selector. */
template <class F, class T, bool IsMemFn = is_memfn<F>::value, bool IsMemObj = is_memobj<F>::value,
          bool IsWrap = is_reference_wrapper_v<local_decay_t<T>>,
          bool IsBase = IsMemFn || IsMemObj ? is_base_match<F, T>::value : false>
struct invoke_tag_select {
  using type = tag_other;
};

// member function — object or direct-base ref
template <class F, class T, bool IsWrap>
struct invoke_tag_select<F, T, true, false, IsWrap, true> {
  using type = tag_memfn_base;
};

// member function — reference_wrapper
template <class F, class T, bool IsBase>
struct invoke_tag_select<F, T, true, false, true, IsBase> {
  using type = tag_memfn_wrap;
};

// member function — pointer / smart-ptr
template <class F, class T>
struct invoke_tag_select<F, T, true, false, false, false> {
  using type = tag_memfn_ptr;
};

// member object — object or direct-base ref
template <class F, class T, bool IsWrap>
struct invoke_tag_select<F, T, false, true, IsWrap, true> {
  using type = tag_memobj_base;
};

// member object — reference_wrapper
template <class F, class T, bool IsBase>
struct invoke_tag_select<F, T, false, true, true, IsBase> {
  using type = tag_memobj_wrap;
};

// member object — pointer / smart-ptr
template <class F, class T>
struct invoke_tag_select<F, T, false, true, false, false> {
  using type = tag_memobj_ptr;
};

/** invoke_impl overloads. */
// tag_memfn_base: (t1.*f)(args...)
template <class F, class T, class... Args>
constexpr auto invoke_impl(tag_memfn_base, F&& f, T&& t1, Args&&... args) noexcept(
    noexcept((::mge::utility::forward<T>(t1).*
              ::mge::utility::forward<F>(f))(::mge::utility::forward<Args>(args)...)))
    -> decltype((::mge::utility::forward<T>(t1).*
                 ::mge::utility::forward<F>(f))(::mge::utility::forward<Args>(args)...)) {
  return (::mge::utility::forward<T>(t1).*
          ::mge::utility::forward<F>(f))(::mge::utility::forward<Args>(args)...);
}

// tag_memfn_wrap: (t1.get().*f)(args...)
template <class F, class T, class... Args>
constexpr auto invoke_impl(tag_memfn_wrap, F&& f, T&& t1, Args&&... args) noexcept(
    noexcept((t1.get().*::mge::utility::forward<F>(f))(::mge::utility::forward<Args>(args)...)))
    -> decltype((t1.get().*::mge::utility::forward<F>(f))(::mge::utility::forward<Args>(args)...)) {
  return (t1.get().*::mge::utility::forward<F>(f))(::mge::utility::forward<Args>(args)...);
}

// tag_memfn_ptr: ((*t1).*f)(args...)
template <class F, class T, class... Args>
constexpr auto invoke_impl(tag_memfn_ptr, F&& f, T&& t1, Args&&... args) noexcept(
    noexcept(((*::mge::utility::forward<T>(t1)).*
              ::mge::utility::forward<F>(f))(::mge::utility::forward<Args>(args)...)))
    -> decltype(((*::mge::utility::forward<T>(t1)).*
                 ::mge::utility::forward<F>(f))(::mge::utility::forward<Args>(args)...)) {
  return ((*::mge::utility::forward<T>(t1)).*
          ::mge::utility::forward<F>(f))(::mge::utility::forward<Args>(args)...);
}

// tag_memobj_base: t1.*f
template <class F, class T>
constexpr auto invoke_impl(tag_memobj_base, F&& f,
                           T&& t1) noexcept(noexcept(::mge::utility::forward<T>(t1).*
                                                     ::mge::utility::forward<F>(f)))
    -> decltype(::mge::utility::forward<T>(t1).*::mge::utility::forward<F>(f)) {
  return ::mge::utility::forward<T>(t1).*::mge::utility::forward<F>(f);
}

// tag_memobj_wrap: t1.get().*f
template <class F, class T>
constexpr auto invoke_impl(tag_memobj_wrap, F&& f,
                           T&& t1) noexcept(noexcept(t1.get().*::mge::utility::forward<F>(f)))
    -> decltype(t1.get().*::mge::utility::forward<F>(f)) {
  return t1.get().*::mge::utility::forward<F>(f);
}

// tag_memobj_ptr: (*t1).*f
template <class F, class T>
constexpr auto invoke_impl(tag_memobj_ptr, F&& f,
                           T&& t1) noexcept(noexcept((*::mge::utility::forward<T>(t1)).*
                                                     ::mge::utility::forward<F>(f)))
    -> decltype((*::mge::utility::forward<T>(t1)).*::mge::utility::forward<F>(f)) {
  return (*::mge::utility::forward<T>(t1)).*::mge::utility::forward<F>(f);
}

// tag_other: f(args...)
template <class F, class... Args>
constexpr auto invoke_impl(tag_other, F&& f, Args&&... args) noexcept(
    noexcept(::mge::utility::forward<F>(f)(::mge::utility::forward<Args>(args)...)))
    -> decltype(::mge::utility::forward<F>(f)(::mge::utility::forward<Args>(args)...)) {
  return ::mge::utility::forward<F>(f)(::mge::utility::forward<Args>(args)...);
}

/** main invoke entry point. */
// zero-arg case
template <class F>
constexpr auto do_invoke(F&& f) noexcept(noexcept(invoke_impl(tag_other{},
                                                              ::mge::utility::forward<F>(f))))
    -> decltype(invoke_impl(tag_other{}, ::mge::utility::forward<F>(f))) {
  return invoke_impl(tag_other{}, ::mge::utility::forward<F>(f));
}

// one-or-more arg case
// Update do_invoke in mge::traits::detail::invoke_impl
template <class F, class T, class... Rest>
constexpr auto do_invoke(F&& f, T&& t1, Rest&&... rest) noexcept(
    noexcept(invoke_impl(typename invoke_tag_select<F, T>::type{}, ::mge::utility::forward<F>(f),
                         ::mge::utility::forward<T>(t1), ::mge::utility::forward<Rest>(rest)...)))
    -> decltype(invoke_impl(typename invoke_tag_select<F, T>::type{}, ::mge::utility::forward<F>(f),
                            ::mge::utility::forward<T>(t1),
                            ::mge::utility::forward<Rest>(rest)...)) {
  return invoke_impl(typename invoke_tag_select<F, T>::type{}, ::mge::utility::forward<F>(f),
                     ::mge::utility::forward<T>(t1), ::mge::utility::forward<Rest>(rest)...);
}
}  // namespace invoke_impl

/** @brief is_invocable helper. */
template <class /*enable*/, class F, class... Args>
struct is_invocable_helper : false_type {};

template <class F, class... Args>
struct is_invocable_helper<invoke_impl::local_void_t<decltype(invoke_impl::do_invoke(
                               ::mge::utility::declval<F>(), ::mge::utility::declval<Args>()...))>,
                           F, Args...> : true_type {};

/** @brief is_invocable_r helper. */
template <class R, class /*enable*/, class F, class... Args>
struct is_invocable_r_helper : false_type {};

template <class F, class... Args>
struct is_invocable_r_helper<
    void,
    invoke_impl::local_void_t<decltype(
        invoke_impl::do_invoke(::mge::utility::declval<F>(), ::mge::utility::declval<Args>()...))>,
    F, Args...> : true_type {};

template <class R, class F, class... Args>
struct is_invocable_r_helper<
    R,
    enable_if_t<!is_void_v<R> && is_convertible_helper<decltype(invoke_impl::do_invoke(
                                                           ::mge::utility::declval<F>(),
                                                           ::mge::utility::declval<Args>()...)),
                                                       R>::value>,
    F, Args...> : true_type {};

/** @brief is_nothrow_invocable helper. */
template <class /*enable*/, class F, class... Args>
struct is_nothrow_invocable_helper : false_type {};

template <class F, class... Args>
struct is_nothrow_invocable_helper<
    invoke_impl::local_void_t<decltype(
        invoke_impl::do_invoke(::mge::utility::declval<F>(), ::mge::utility::declval<Args>()...))>,
    F, Args...>
    : bool_constant<noexcept(invoke_impl::do_invoke(::mge::utility::declval<F>(),
                                                    ::mge::utility::declval<Args>()...))> {};

/** @brief is_nothrow_r_invocable helper. */
template <class R, class /*enable*/, class F, class... Args>
struct is_nothrow_invocable_r_helper : false_type {};

template <class R, class F, class... Args>
struct is_nothrow_invocable_r_helper<
    R, enable_if_t<is_invocable_r_helper<R, void, F, Args...>::value>, F, Args...>
    : bool_constant<noexcept(invoke_impl::do_invoke(::mge::utility::declval<F>(),
                                                    ::mge::utility::declval<Args>()...))> {};
// #endregion

}  // namespace mge::traits::detail
// #endregion

// #region Public API
namespace mge::traits {

// #region Relationship Trait - Same
/**
 * @brief A type used to check if two objects are same.
 * @tparam T Type of the 1st object.
 * @tparam U Type of the 2nd object.
 * @ingroup traits
 */
template <typename T, typename U>
struct MGE_API_TEMPLATE is_same : detail::is_same_helper<T, U> {};

/**
 * @brief Value alias for is_same.
 * @ingroup traits
 */
template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;
// #endregion

// #region Relationship Trait - Convertible
/**
 * @brief A type used to check if an object is convertible to other object.
 * @tparam T Type of the 1st object.
 * @tparam U Type of the 2nd object.
 * @ingroup traits
 */
template <typename T, typename U>
struct MGE_API_TEMPLATE is_convertible : detail::is_convertible_helper<T, U> {};

/**
 * @brief Value alias for is_convertible.
 * @ingroup traits
 */
template <typename T, typename U>
inline constexpr bool is_convertible_v = is_convertible<T, U>::value;
// #endregion

// #region Relationship Trait - Base Of
/**
 * @brief A type used to check if an object is base of other object.
 * @tparam T Type of the 1st object.
 * @tparam U Type of the 2nd object.
 * @ingroup traits
 */
template <typename T, typename U>
struct MGE_API_TEMPLATE is_base_of : detail::is_base_of_helper<T, U> {};

/**
 * @brief Value alias for is_base_of.
 * @ingroup traits
 */
template <typename T, typename U>
inline constexpr bool is_base_of_v = is_base_of<T, U>::value;
// #endregion

// #region Relationship Trait - Virtual Base Of
/**
 * @brief A type used to check if an object is virtual_base of other object.
 * @tparam T Type of the 1st object.
 * @tparam U Type of the 2nd object.
 * @ingroup traits
 */
template <typename T, typename U>
struct MGE_API_TEMPLATE is_virtual_base_of : detail::is_virtual_base_of_helper<T, U> {};

/**
 * @brief Value alias for is_virtual_base_of.
 * @ingroup traits
 */
template <typename T, typename U>
inline constexpr bool is_virtual_base_of_v = is_virtual_base_of<T, U>::value;
// #endregion

// #region Relationship Trait - Invocable
/**
 * @brief A type used to check if an object (fn) is invocable by given args.
 * @tparam F Type of the object (fn).
 * @tparam Args Arguments.
 * @ingroup traits
 */
template <typename F, typename... Args>
struct MGE_API_TEMPLATE is_invocable : detail::is_invocable_helper<void, F, Args...> {};

/**
 * @brief Value alias for is_same.
 * @ingroup traits
 */
template <typename F, typename... Args>
inline constexpr bool is_invocable_v = is_invocable<F, Args...>::value;
// #endregion

// #region Relationship Trait - Invocable R
/**
 * @brief A type used to check if an object (fn) is invocable by given args and gives a specific
 *       result.
 * @tparam R Type of the return.
 * @tparam F Type of the object (fn).
 * @tparam Args Arguments.
 * @ingroup traits
 */
template <typename R, typename F, typename... Args>
struct MGE_API_TEMPLATE is_invocable_r : detail::is_invocable_r_helper<R, void, F, Args...> {};

/**
 * @brief Value alias for is_same.
 * @ingroup traits
 */
template <typename R, typename F, typename... Args>
inline constexpr bool is_invocable_r_v = is_invocable_r<R, F, Args...>::value;
// #endregion

// #region Relationship Trait - Nothrow Invocable
/**
 * @brief A type used to check if an object (fn) is nothrow invocable by given args.
 * @tparam F Type of the object (fn).
 * @tparam Args Arguments.
 * @ingroup traits
 */
template <typename F, typename... Args>
struct MGE_API_TEMPLATE is_nothrow_invocable
    : detail::is_nothrow_invocable_helper<void, F, Args...> {};

/**
 * @brief Value alias for is_same.
 * @ingroup traits
 */
template <typename F, typename... Args>
inline constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<F, Args...>::value;
// #endregion

// #region Relationship Trait - Nothrow Invocable R
/**
 * @brief A type used to check if an object (fn) is nothrow invocable by given args and gives a
 *        specific result.
 * @tparam R Type of the return.
 * @tparam F Type of the object (fn).
 * @tparam Args Arguments.
 * @ingroup traits
 */
template <typename R, typename F, typename... Args>
struct MGE_API_TEMPLATE is_nothrow_invocable_r
    : detail::is_nothrow_invocable_r_helper<R, void, F, Args...> {};

/**
 * @brief Value alias for is_same.
 * @ingroup traits
 */
template <typename R, typename F, typename... Args>
inline constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<R, F, Args...>::value;
// #endregion

}  // namespace mge::traits
// #endregion
