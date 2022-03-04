#ifndef TLPP_TYPE_TRAITS_ARRAY_TRAITS_HPP
#define TLPP_TYPE_TRAITS_ARRAY_TRAITS_HPP

#include <Tlpp/Config.h>
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
		inline constexpr size_t rank_v = 0;

		template<typename T>
		inline constexpr size_t rank_v<T[]> = rank_v<T> + 1;

		template<typename T, size_t N>
		inline constexpr size_t rank_v<T[N]> = rank_v<T> + 1;

		template<typename T>
		struct rank : integral_constant<size_t, rank_v<T>>
		{};

		template<typename T, unsigned N = 0>
		inline constexpr size_t extent_v = 0;

		template<typename T>
		inline constexpr size_t extent_v<T[], 0> = 0;

		template<typename T, unsigned N>
		inline constexpr size_t extent_v<T[], N> = extent_v<T, N - 1>;

		template<typename T, size_t I>
		inline constexpr size_t extent_v<T[I], 0> = I;

		template<typename T, size_t I, unsigned N>
		inline constexpr size_t extent_v<T[I], N> = extent_v<T, N - 1>;

		template<typename T, unsigned N = 0>
		struct extent : integral_constant<size_t, extent_v<T, N>>
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