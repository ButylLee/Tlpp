#ifndef TLPP_TYPE_TRAITS_REMOVE_CVREF_HPP
#define TLPP_TYPE_TRAITS_REMOVE_CVREF_HPP

#include <Tlpp/TypeTraits/cv_traits.hpp>
#include <Tlpp/TypeTraits/integral_constant.hpp>
#include <Tlpp/TypeTraits/ref_traits.hpp>

namespace tl
{
	namespace type_traits
	{
		template<typename T>
		struct remove_cvref
		{
			using type = remove_cv_t<remove_reference_t<T>>;
		};

		template<typename T>
		using remove_cvref_t = typename remove_cvref<T>::type;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_REMOVE_CVREF_HPP