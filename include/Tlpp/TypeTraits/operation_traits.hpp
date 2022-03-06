#ifndef TLPP_TYPE_TRAITS_OPERATION_TRAITS_HPP
#define TLPP_TYPE_TRAITS_OPERATION_TRAITS_HPP

#include <Tlpp/Config.h>
#include <Tlpp/TypeTraits/cv_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>
#include <Tlpp/TypeTraits/ref_traits.hpp>
#include <Tlpp/Utility/DeclVal.hpp>

namespace tl
{
	namespace type_traits
	{
#if defined TLPP_MSVC || defined TLPP_GCC || defined TLPP_CLANG
		template<typename T, typename... Args>
		inline constexpr bool
			is_constructible_v = __is_constructible(T, Args...);
#else
#pragma message("Not support constructible traits.")
		template<typename T, typename... Args>
		inline constexpr bool is_constructible_v = false;
#endif
		template<typename T, typename... Args>
		struct is_constructible : bool_constant<is_constructible_v<T, Args...>>
		{};

		template<typename T>
		inline constexpr bool is_default_constructible_v =
			is_constructible_v<T>;

		template<typename T>
		struct is_default_constructible
			: bool_constant<is_default_constructible_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_copy_constructible_v =
			is_constructible_v<T, add_lvalue_reference_t<add_const_t<T>>>;

		template<typename T>
		struct is_copy_constructible : bool_constant<is_copy_constructible_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_move_constructible_v =
			is_constructible_v<T, add_rvalue_reference_t<T>>;

		template<typename T>
		struct is_move_constructible : bool_constant<is_move_constructible_v<T>>
		{};

#if defined TLPP_MSVC || defined TLPP_GCC || defined TLPP_CLANG
		template<typename T, typename U>
		inline constexpr bool is_assignable_v = __is_assignable(T, U);
#else
		// TODO
#endif
		template<typename T, typename U>
		struct is_assignable : bool_constant<is_assignable_v<T, U>>
		{};

		template<typename T>
		inline constexpr bool is_copy_assignable_v =
			is_assignable_v<add_lvalue_reference_t<T>,
		                    add_lvalue_reference_t<add_const_t<T>>>;

		template<typename T>
		struct is_copy_assignable : bool_constant<is_copy_assignable_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_move_assignable_v =
			is_assignable_v<add_lvalue_reference_t<T>,
		                    add_rvalue_reference_t<T>>;

		template<typename T>
		struct is_move_assignable : bool_constant<is_move_assignable_v<T>>
		{};

#if defined TLPP_MSVC || defined TLPP_GCC || defined TLPP_CLANG
		template<typename T>
		inline constexpr bool is_destructible_v = __is_destructible(T);
#else
		// TODO
#endif
		template<typename T>
		struct is_destructible : bool_constant<is_destructible_v<T>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_OPERATION_TRAITS_HPP