#ifndef TLPP_TYPE_TRAITS_TYPE_RELATIONSHIPS_HPP
#define TLPP_TYPE_TRAITS_TYPE_RELATIONSHIPS_HPP

#include <Tlpp/TypeTraits/basic_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>
#include <Tlpp/TypeTraits/voi>

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

#if defined TLPP_MSVC || defined TLPP_GCC || defined TLPP_CLANG
		template<typename Base, typename Derived>
		inline constexpr bool is_base_of_v = __is_base_of(Base, Derived);
#else
		namespace detail
		{
			template<typename Base>
			true_type test_base_of(const volatile Base*);
			template<typename>
			false_type test_base_of(const volatile void*);

			template<typename, typename>
			false_type is_base_of_impl(...);
			template<typename Base, typename Derived>
			decltype(test_base_of<Base>(static_cast<Derived*>(nullptr)))
			is_base_of_impl(int);
		} // namespace detail
		template<typename Base, typename Derived>
		inline constexpr bool is_base_of_v = is_class_v<Base> &&
			is_class_v<Derived> && decltype(detail::is_base_of_impl<Base,
		                                                           Derived>(
				0))::value;
#endif
		template<typename Base, typename Derived>
		struct is_base_of : bool_constant<is_base_of_v<Base, Derived>>
		{};

#if defined TLPP_MSVC || defined TLPP_CLANG
		template<typename From, typename To>
		inline constexpr bool is_convertible_v = __is_convertible_to(From, To);
#else
		namespace detail
		{
			template<typename From, typename To, typename = void>
			inline constexpr bool is_convertible_impl = false;
			template<typename From, typename To>
			inline constexpr bool is_convertible_impl<
				From,
				To,
				void_t<decltype(utility::DeclVal<void (&)(To)>()(
					utility::DeclVal<From>()))>> = true;
		} // namespace detail
		template<typename From, typename To>
		inline constexpr bool is_convertible_v =
			is_void_t<From> && is_void_t<To> ||
			detail::is_convertible_impl<From, To>;
#endif
		template<typename From, typename To>
		struct is_convertible : bool_constant<is_convertible_v<From, To>>
		{};

		template<typename From, typename To>
		inline constexpr bool
			is_nothrow_convertible_v = is_convertible_v<From, To> && noexcept(
				utility::DeclVal<void (&)(To) noexcept>()(
					utility::DeclVal<From>()));

		template<typename From, typename To>
		struct is_nothrow_convertible
			: bool_constant<is_nothrow_convertible_v<From, To>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_TYPE_RELATIONSHIPS_HPP