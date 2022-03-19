#ifndef TLPP_TYPE_TRAITS_POINTER_TRAITS_HPP
#define TLPP_TYPE_TRAITS_POINTER_TRAITS_HPP

#include <Tlpp/Config.h>
#include <Tlpp/TypeTraits/cv_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>
#include <Tlpp/TypeTraits/ref_traits.hpp>
#include <Tlpp/TypeTraits/void_t.hpp>

namespace tl
{
	namespace type_traits
	{
		namespace detail
		{
			template<typename>
			inline constexpr bool is_pointer_impl = false;

			template<typename T>
			inline constexpr bool is_pointer_impl<T*> = true;
		} // namespace detail

		template<typename T>
		inline constexpr bool is_pointer_v = detail::is_pointer_impl<remove_cv_t<T>>;

		template<typename T>
		struct is_pointer : bool_constant<is_pointer_v<T>>
		{};

		namespace detail
		{
			template<typename T, typename = void>
			struct try_add_pointer
			{
				using type = T;
			};

			template<typename T>
			struct try_add_pointer<T, void_t<remove_reference_t<T>*>>
			{
				using type = remove_reference_t<T>*;
			};

		} // namespace detail

		template<typename T>
		struct add_pointer
		{
			using type = detail::try_add_pointer<T>::type;
		};

		template<typename T>
		using add_pointer_t = typename add_pointer<T>::type;

		namespace detail
		{
			template<typename T>
			struct try_remove_pointer
			{
				using type = T;
			};

			template<typename T>
			struct try_remove_pointer<T*>
			{
				using type = T;
			};

		} // namespace detail

		template<typename T>
		struct remove_pointer
		{
			using type = detail::try_remove_pointer<remove_cv_t<T>>::type;
		};

		template<typename T>
		using remove_pointer_t = typename remove_pointer<T>::type;

		namespace detail
		{
			template<typename T>
			struct is_member_pointer_impl
			{
				static constexpr bool is_member = false;
				static constexpr bool is_func = false;
				static constexpr bool is_object = false;
			};

			template<typename T, typename C>
			struct is_member_pointer_impl<T C::*>
			{
				static constexpr bool is_member = true;
				static constexpr bool is_func = is_function_v<T>;
				static constexpr bool is_object = !is_func;
			};

		} // namespace detail

#ifdef TLPP_CLANG
		template<typename T>
		inline constexpr bool
			is_member_object_pointer_v = __is_member_object_pointer(T);
#else
		template<typename T>
		inline constexpr bool is_member_object_pointer_v =
			detail::is_member_pointer_impl<remove_cv_t<T>>::is_object
#endif
		template<typename T>
		struct is_member_object_pointer
			: bool_constant<is_member_object_pointer_v<T>>
		{};

#ifdef TLPP_CLANG
		template<typename T>
		inline constexpr bool
			is_member_function_pointer_v = __is_member_function_pointer(T);
#else
		template<typename T>
		inline constexpr bool is_member_function_pointer_v =
			detail::is_member_pointer_impl<remove_cv_t<T>>::is_func;
#endif
		template<typename T>
		struct is_member_function_pointer
			: bool_constant<is_member_function_pointer_v<T>>
		{};

#ifdef TLPP_CLANG
		template<typename T>
		inline constexpr bool is_member_pointer_v = __is_member_pointer(T);
#else
		template<typename T>
		inline constexpr bool is_member_pointer_v =
			detail::is_member_pointer_impl<remove_cv_t<T>>::is_member;
#endif
		template<typename T>
		struct is_member_pointer : bool_constant<is_member_pointer_v<T>>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_POINTER_TRAITS_HPP