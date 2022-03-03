#ifndef TLPP_TYPE_TRAITS_REF_TRAITS_HPP
#define TLPP_TYPE_TRAITS_REF_TRAITS_HPP

#include <Tlpp/TypeTraits/integral_constant.hpp>

namespace tl
{
	namespace type_traits
	{
		template<typename T>
		inline constexpr bool is_lvalue_reference_v = false;

		template<typename T>
		inline constexpr bool is_lvalue_reference_v<T&> = true;

		template<typename T>
		struct is_lvalue_reference : bool_constant<is_lvalue_reference_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_rvalue_reference_v = false;

		template<typename T>
		inline constexpr bool is_rvalue_reference_v<T&&> = true;

		template<typename T>
		struct is_rvalue_reference : bool_constant<is_rvalue_reference_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_reference_v =
			is_lvalue_reference_v<T> || is_rvalue_reference_v<T>;

		template<typename T>
		struct is_reference : bool_constant<is_reference_v<T>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_REF_TRAITS_HPP