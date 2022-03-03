#ifndef TLPP_TYPE_TRAITS_BASIC_TRAITS_HPP
#define TLPP_TYPE_TRAITS_BASIC_TRAITS_HPP

#include <Tlpp/Config.h>
#include <Tlpp/TypeTraits/array_traits.hpp>
#include <Tlpp/TypeTraits/cv_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>
#include <Tlpp/TypeTraits/pointer_traits.hpp>
#include <Tlpp/TypeTraits/ref_traits.hpp>
#include <Tlpp/TypeTraits/type_relationships.hpp>

namespace tl
{
	namespace type_traits
	{
		template<typename T>
		inline constexpr bool is_void_v = is_same_v<remove_cv_t<T>, void>;

		template<typename T>
		struct is_void : bool_constant<is_void_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_null_pointer_v =
			is_same_v<remove_cv_t<T>, decltype(nullptr)>;

		template<typename T>
		struct is_null_pointer : bool_constant<is_null_pointer_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_integral_v =
			detail::is_any_of_v<remove_cv_t<T>,
		                        bool,
		                        char,
		                        wchar_t,
		                        char8_t,
		                        char16_t,
		                        char32_t,
		                        signed char,
		                        unsigned char,
		                        short,
		                        unsigned short,
		                        int,
		                        unsigned int,
		                        long,
		                        unsigned long,
		                        long long,
		                        unsigned long long>;

		template<typename T>
		struct is_integral : bool_constant<is_integral_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_floating_point_v =
			detail::is_any_of_v<remove_cv_t<T>, float, double, long double>;

		template<typename T>
		struct is_floating_point : bool_constant<is_floating_point_v<T>>
		{};

#if defined TLPP_MSVC || defined TLPP_GCC || defined TLPP_CLANG
		template<typename T>
		inline constexpr bool is_union_v = __is_union(T);
#else
		template<typename T>
		inline constexpr bool is_union_v =
			false; // always false if not supprt builtin __is_union
#endif
		template<typename T>
		struct is_union : bool_constant<is_union_v<T>>
		{};

#if defined TLPP_MSVC || defined TLPP_GCC || defined TLPP_CLANG
		template<typename T>
		inline constexpr bool is_class_v = __is_class(T);
#else
		namespace detail
		{
			template<typename>
			inline constexpr bool is_class_impl = false;
			template<typename T>
			inline constexpr bool is_class_impl<int T::*> = true;
		} // namespace detail

		template<typename T>
		inline constexpr bool is_class_v =
			detail::is_class_impl<T> && !is_union_v<T>;
#endif
		template<typename T>
		struct is_class : bool_constant<is_class_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_function_v =
			!is_const_v<add_const_t<T>> && !is_reference_v<T>;

		template<typename T>
		struct is_function : bool_constant<is_function_v<T>>
		{};

#if defined TLPP_MSVC || defined TLPP_GCC || defined TLPP_CLANG
		template<typename T>
		inline constexpr bool is_enum_v = __is_enum(T);
#else
		template<typename T>
		inline constexpr bool is_enum_v =
			!(is_void_v<T> || is_integral_v<T> || is_floating_point_v<T> ||
		      is_array_v<T> || is_pointer_v<T> || is_member_pointer_v<T> ||
		      is_union_v<T> || is_function_v<T> || is_reference_v<T> ||
		      is_class_v<T>);
#endif
		template<typename T>
		struct is_enum : bool_constant<is_enum_v<T>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_BASIC_TRAITS_HPP