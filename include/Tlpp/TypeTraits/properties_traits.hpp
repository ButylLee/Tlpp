#ifndef TLPP_TYPE_TRAITS_PROPERTIES_TRAITS_HPP
#define TLPP_TYPE_TRAITS_PROPERTIES_TRAITS_HPP

#include <Tlpp/Config.h>
#include <Tlpp/TypeTraits/operation_traits.hpp>

namespace tl
{
	namespace type_traits
	{
#if defined TLPP_MSVC || defined TLPP_GCC || defined TLPP_CLANG
		template<typename T>
		inline constexpr bool is_trivial_v = __is_trivial(T);
#else
		template<typename T>
		inline constexpr bool is_trivial_v = is_trivially_copyable_v<T>&&
			is_trivially_default_constructible_v<T>;
#endif
		template<typename T>
		struct is_trivial : bool_constant<is_trivial_v<T>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_PROPERTIES_TRAITS_HPP