#ifndef TLPP_TYPE_TRAITS_TYPE_RELATIONSHIPS_HPP
#define TLPP_TYPE_TRAITS_TYPE_RELATIONSHIPS_HPP

#include <Tlpp/TypeTraits/integral_constant.hpp>

namespace tl
{
	namespace type_traits
	{
		template<typename T, typename U>
		inline constexpr bool is_same_v = false;

		template<typename T>
		inline constexpr bool is_same_v<T, T> = true;

		template<typename T, typename U>
		struct is_same : bool_constant<is_same_v<T, U>>
		{};

		namespace detail
		{
			template<typename T, typename... Ts>
			inline constexpr bool is_any_of_v = (is_same_v<T, Ts> || ...);
		}

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_TYPE_RELATIONSHIPS_HPP