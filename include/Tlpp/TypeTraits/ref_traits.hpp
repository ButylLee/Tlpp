#ifndef TLPP_TYPE_TRAITS_REF_TRAITS_HPP
#define TLPP_TYPE_TRAITS_REF_TRAITS_HPP

#include <Tlpp/TypeTraits/integral_constant.hpp>
#include <Tlpp/TypeTraits/void_t.hpp>

namespace tl
{
	namespace type_traits
	{
		template<typename>
		inline constexpr bool is_lvalue_reference_v = false;

		template<typename T>
		inline constexpr bool is_lvalue_reference_v<T&> = true;

		template<typename T>
		struct is_lvalue_reference : bool_constant<is_lvalue_reference_v<T>>
		{};

		template<typename>
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

		template<typename T>
		struct remove_reference
		{
			using type = T;
		};

		template<typename T>
		struct remove_reference<T&>
		{
			using type = T;
		};

		template<typename T>
		struct remove_reference<T&&>
		{
			using type = T;
		};

		template<typename T>
		using remove_reference_t = typename remove_reference<T>::type;

		namespace detail
		{
			template<typename T, typename = void>
			struct try_add_reference
			{
				using lvalue_type = T;
				using rvalue_type = T;
			};

			template<typename T>
			struct try_add_reference<T, void_t<T&, T&&>>
			{
				using lvalue_type = T&;
				using rvalue_type = T&&;
			};
		} // namespace detail

		template<typename T>
		struct add_lvalue_reference
		{
			using type = typename detail::try_add_reference<T>::lvalue_type;
		};

		template<typename T>
		using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

		template<typename T>
		struct add_rvalue_reference
		{
			using type = typename detail::try_add_reference<T>::rvalue_type;
		};

		template<typename T>
		using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_REF_TRAITS_HPP