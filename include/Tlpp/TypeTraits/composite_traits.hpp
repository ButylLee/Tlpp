#ifndef TLPP_TYPE_TRAITS_COMPOSITE_TRAITS_HPP
#define TLPP_TYPE_TRAITS_COMPOSITE_TRAITS_HPP

#include <Tlpp/TypeTraits/basic_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>
#include <Tlpp/TypeTraits/pointer_traits.hpp>

namespace tl
{
	namespace type_traits
	{
		template<typename T>
		inline constexpr bool is_arithmetic_v =
			is_integral_v<T> || is_floating_point_v<T>;

		template<typename T>
		struct is_arithmetic : bool_constant<is_arithmetic_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_fundamental_v =
			is_arithmetic_v<T> || is_void_v<T> || is_null_pointer_v<T>;

		template<typename T>
		struct is_fundamental : bool_constant<is_fundamental_v<T>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_COMPOSITE_TRAITS_HPP