#ifndef TLPP_TYPE_TRAITS_TRAITS_OPERATIONS_HPP
#define TLPP_TYPE_TRAITS_TRAITS_OPERATIONS_HPP

#include <Tlpp/TypeTraits/conditional.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>

namespace tl
{
	namespace type_traits
	{
		template<typename...>
		struct conjunction : true_type
		{};

		template<typename T>
		struct conjunction<T> : T
		{};

		template<typename T, typename... Ts>
		struct conjunction<T, Ts...>
			: conditional_t<bool(T::value), conjunction<Ts...>, T>
		{};

		template<typename... Ts>
		inline constexpr bool conjunction_v = conjunction<Ts...>::value;

		template<typename...>
		struct disjunction : false_type
		{};

		template<typename T>
		struct disjunction<T> : T
		{};

		template<typename T, typename... Ts>
		struct disjunction<T, Ts...>
			: conditional_t<bool(T::value), T, disjunction<Ts...>>
		{};

		template<typename... Ts>
		inline constexpr bool disjunction_v = disjunction<Ts...>::value;

		template<typename T>
		struct negation : bool_constant<!bool(T::value)>
		{};

		template<typename T>
		inline constexpr bool negation_v = negation<T>::value;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_TRAITS_OPERATIONS_HPP