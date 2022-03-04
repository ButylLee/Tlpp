#ifndef TLPP_TYPE_TRAITS_COMPOSITE_TRAITS_HPP
#define TLPP_TYPE_TRAITS_COMPOSITE_TRAITS_HPP

#include <Tlpp/TypeTraits/basic_traits.hpp>
#include <Tlpp/TypeTraits/cv_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>
#include <Tlpp/TypeTraits/pointer_traits.hpp>
#include <Tlpp/TypeTraits/type_relationships.hpp>

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

		template<typename T>
		inline constexpr bool is_scalar_v =
			is_arithmetic_v<T> || is_enum_v<T> || is_pointer_v<T> ||
			is_member_pointer_v<T> || is_null_pointer_v<T>;

		template<typename T>
		struct is_scalar : bool_constant<is_scalar_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_object_v =
			is_const_v<add_const_t<T>> && !is_void_v<T>;

		template<typename T>
		struct is_object : bool_constant<is_object_v<T>>
		{};

		template<typename T>
		inline constexpr bool is_compound_v = !is_fundamental_v<T>;

		template<typename T>
		struct is_compound : bool_constant<is_compound_v<T>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_COMPOSITE_TRAITS_HPP