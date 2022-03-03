﻿#ifndef TLPP_TYPE_TRAITS_BASIC_TRAITS_HPP
#define TLPP_TYPE_TRAITS_BASIC_TRAITS_HPP

#include <Tlpp/Config.h>
#include <Tlpp/TypeTraits/cv_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>
#include <Tlpp/TypeTraits/type_relationships.hpp>

#ifndef TLPP_MSVC
#include <cstddef>
#endif

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

		template<typename T>
		inline constexpr bool is_array_v = false;

		template<typename T>
		inline constexpr bool is_array_v<T[]> = true;

		template<typename T, size_t N>
		inline constexpr bool is_array_v<T[N]> = true;

		template<typename T>
		struct is_array : bool_constant<is_array_v<T>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_BASIC_TRAITS_HPP