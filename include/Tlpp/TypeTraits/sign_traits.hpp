#ifndef TLPP_TYPE_TRAITS_SIGN_TRAITS_HPP
#define TLPP_TYPE_TRAITS_SIGN_TRAITS_HPP

#include <Tlpp/Config.h>
#include <Tlpp/TypeTraits/basic_traits.hpp>
#include <Tlpp/TypeTraits/composite_traits.hpp>
#include <Tlpp/TypeTraits/conditional.hpp>
#include <Tlpp/TypeTraits/cv_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>

#ifndef TLPP_MSVC
#include <cstddef>
#endif

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

		namespace detail
		{
			template<size_t S, typename T, typename... Ts>
			struct apply_first_type_of_size
			{
				using type =
					conditional_t<sizeof(T) < S,
				                  apply_first_type_of_size<S, Ts...>::type,
				                  T>;
			};

			template<size_t S, typename T>
			struct apply_first_type_of_size<S, T>
			{
				using type = T;
			};

			template<typename T,
			         bool = is_integral_except_bool_v<T> || is_enum_v<T>>
			struct make_signed_impl;

			template<typename T>
			struct make_signed_impl<T, true>
			{
				using type = apply_first_type_of_size<sizeof(T),
				                                      signed char,
				                                      signed short,
				                                      signed int,
				                                      signed long,
				                                      signed long long>::type;
			};

			template<>
			struct make_signed_impl<signed char, true>
			{
				using type = signed char;
			};

			template<>
			struct make_signed_impl<unsigned char, true>
			{
				using type = signed char;
			};

			template<>
			struct make_signed_impl<signed short, true>
			{
				using type = signed short;
			};

			template<>
			struct make_signed_impl<unsigned short, true>
			{
				using type = signed short;
			};

			template<>
			struct make_signed_impl<signed int, true>
			{
				using type = signed int;
			};

			template<>
			struct make_signed_impl<unsigned int, true>
			{
				using type = signed int;
			};

			template<>
			struct make_signed_impl<signed long, true>
			{
				using type = signed long;
			};

			template<>
			struct make_signed_impl<unsigned long, true>
			{
				using type = signed long;
			};

			template<>
			struct make_signed_impl<signed long long, true>
			{
				using type = signed long long;
			};

			template<>
			struct make_signed_impl<unsigned long long, true>
			{
				using type = signed long long;
			};

			template<typename T,
			         bool = is_integral_except_bool_v<T> || is_enum_v<T>>
			struct make_unsigned_impl;

			template<typename T>
			struct make_unsigned_impl<T, true>
			{
				using type = apply_first_type_of_size<sizeof(T),
				                                      unsigned char,
				                                      unsigned short,
				                                      unsigned int,
				                                      unsigned long,
				                                      unsigned long long>::type;
			};

			template<>
			struct make_unsigned_impl<signed char, true>
			{
				using type = unsigned char;
			};

			template<>
			struct make_unsigned_impl<unsigned char, true>
			{
				using type = unsigned char;
			};

			template<>
			struct make_unsigned_impl<signed short, true>
			{
				using type = unsigned short;
			};

			template<>
			struct make_unsigned_impl<unsigned short, true>
			{
				using type = unsigned short;
			};

			template<>
			struct make_unsigned_impl<signed int, true>
			{
				using type = unsigned int;
			};

			template<>
			struct make_unsigned_impl<unsigned int, true>
			{
				using type = unsigned int;
			};

			template<>
			struct make_unsigned_impl<signed long, true>
			{
				using type = unsigned long;
			};

			template<>
			struct make_unsigned_impl<unsigned long, true>
			{
				using type = unsigned long;
			};

			template<>
			struct make_unsigned_impl<signed long long, true>
			{
				using type = unsigned long long;
			};

			template<>
			struct make_unsigned_impl<unsigned long long, true>
			{
				using type = unsigned long long;
			};

		} // namespace detail

		template<typename T>
		struct make_signed
		{
			static_assert(detail::is_integral_except_bool_v<T> || is_enum_v<T>,
			              "make_signed<T> requires an integral type except "
			              "bool or an enum type which may cv-qualified.");
			using type = detail::
				copy_cv_t<T, detail::make_signed_impl<remove_cv_t<T>>::type>;
		};

		template<typename T>
		using make_signed_t = make_signed<T>::type;

		template<typename T>
		struct make_unsigned
		{
			static_assert(detail::is_integral_except_bool_v<T> || is_enum_v<T>,
			              "make_signed<T> requires an integral type except "
			              "bool or an enum type which may cv-qualified.");
			using type = detail::
				copy_cv_t<T, detail::make_unsigned_impl<remove_cv_t<T>>::type>;
		};

		template<typename T>
		using make_unsigned_t = make_unsigned<T>::type;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_SIGN_TRAITS_HPP