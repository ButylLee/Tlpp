#ifndef TLPP_TYPE_TRAITS_CV_TRAITS_HPP
#define TLPP_TYPE_TRAITS_CV_TRAITS_HPP

#include <Tlpp/TypeTraits/integral_constant.hpp>

namespace tl
{
	namespace type_traits
	{
		template<typename>
		inline constexpr bool is_const_v = false;

		template<typename T>
		inline constexpr bool is_const_v<const T> = true;

		template<typename T>
		struct is_const : bool_constant<is_const_v<T>>
		{};

		template<typename>
		inline constexpr bool is_volatile_v = false;

		template<typename T>
		inline constexpr bool is_volatile_v<volatile T> = true;

		template<typename T>
		struct is_volatile : bool_constant<is_volatile_v<T>>
		{};

		template<typename T>
		struct add_const
		{
			using type = const T;
		};

		template<typename T>
		using add_const_t = typename add_const<T>::type;

		template<typename T>
		struct add_volatile
		{
			using type = volatile T;
		};

		template<typename T>
		using add_volatile_t = typename add_volatile<T>::type;

		template<typename T>
		struct add_cv
		{
			using type = const volatile T;
		};

		template<typename T>
		using add_cv_t = typename add_cv<T>::type;

		template<typename T>
		struct remove_const
		{
			using type = T;
		};

		template<typename T>
		struct remove_const<const T>
		{
			using type = T;
		};

		template<typename T>
		using remove_const_t = typename remove_const<T>::type;

		template<typename T>
		struct remove_volatile
		{
			using type = T;
		};

		template<typename T>
		struct remove_volatile<volatile T>
		{
			using type = T;
		};

		template<typename T>
		using remove_volatile_t = typename remove_volatile<T>::type;

		template<typename T>
		struct remove_cv
		{
			using type = T;
		};

		template<typename T>
		struct remove_cv<const T>
		{
			using type = T;
		};

		template<typename T>
		struct remove_cv<volatile T>
		{
			using type = T;
		};

		template<typename T>
		struct remove_cv<const volatile T>
		{
			using type = T;
		};

		template<typename T>
		using remove_cv_t = typename remove_cv<T>::type;

		namespace detail
		{
			template<typename From, typename To>
			struct copy_cv
			{
				using type = To;
			};

			template<typename From, typename To>
			struct copy_cv<const From, To>
			{
				using type = const To;
			};

			template<typename From, typename To>
			struct copy_cv<volatile From, To>
			{
				using type = volatile To;
			};

			template<typename From, typename To>
			struct copy_cv<const volatile From, To>
			{
				using type = const volatile To;
			};

			template<typename From, typename To>
			using copy_cv_t = typename copy_cv<From, To>::type;

		} // namespace detail

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_CV_TRAITS_HPP