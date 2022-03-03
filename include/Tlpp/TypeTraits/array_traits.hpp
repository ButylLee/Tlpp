#ifndef TLPP_TYPE_TRAITS_ARRAY_TRAITS_HPP
#define TLPP_TYPE_TRAITS_ARRAY_TRAITS_HPP

#include <Tlpp/TypeTraits/integral_constant.hpp>

#ifndef TLPP_MSVC
#include <cstddef>
#endif

namespace tl
{
	namespace type_traits
	{
		template<typename>
		inline constexpr bool is_array_v = false;

		template<typename T>
		inline constexpr bool is_array_v<T[]> = true;

		template<typename T, size_t N>
		inline constexpr bool is_array_v<T[N]> = true;

		template<typename T>
		struct is_array : bool_constant<is_array_v<T>>
		{};

		template<typename T>
		struct remove_extent
		{
			using type = T;
		};

		template<typename T>
		struct remove_extent<T[]>
		{
			using type = T;
		};

		template<typename T, size_t N>
		struct remove_extent<T[N]>
		{
			using type = T;
		};

		template<typename T>
		using remove_extent_t = typename remove_extent<T>::type;

		template<typename T>
		struct remove_all_extents
		{
			using type = T;
		};

		template<typename T>
		struct remove_all_extents<T[]>
		{
			using type = remove_all_extents<T>::type;
		};

		template<typename T, size_t N>
		struct remove_all_extents<T[N]>
		{
			using type = remove_all_extents<T>::type;
		};

		template<typename T>
		using remove_all_extents_t = typename remove_all_extents<T>::type;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_ARRAY_TRAITS_HPP