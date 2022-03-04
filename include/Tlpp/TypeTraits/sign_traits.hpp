#ifndef TLPP_TYPE_TRAITS_SIGN_TRAITS_HPP
#define TLPP_TYPE_TRAITS_SIGN_TRAITS_HPP

#include <Tlpp/Config.h>
#include <Tlpp/TypeTraits/composite_traits.hpp>
#include <Tlpp/TypeTraits/cv_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>

namespace tl
{
	namespace type_traits
	{
		namespace detail
		{
			template<typename T, bool = is_arithmetic_v<T>>
			struct sign_info
			{
				static constexpr bool is_signed = false;
				static constexpr bool is_unsigned = false;
			};

			template<typename T>
			struct sign_info<T, true>
			{
				static constexpr bool is_signed = T(-1) < T(0);
				static constexpr bool is_unsigned = T(0) < T(-1);
			};

		} // namespace detail

#ifdef TLPP_CLANG
		template<typename T>
		inline constexpr bool is_signed_v = __is_signed(T);
#else
		template<typename T>
		inline constexpr bool is_signed_v = detail::sign_info<T>::is_signed;
#endif
		template<typename T>
		struct is_signed : bool_constant<is_signed_v<T>>
		{};

#ifdef TLPP_CLANG
		template<typename T>
		inline constexpr bool is_unsigned_v = __is_unsigned(T);
#else
		template<typename T>
		inline constexpr bool is_unsigned_v = detail::sign_info<T>::is_unsigned;
#endif
		template<typename T>
		struct is_unsigned : bool_constant<is_unsigned_v<T>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_SIGN_TRAITS_HPP