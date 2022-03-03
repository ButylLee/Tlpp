#ifndef TLPP_TYPE_TRAITS_DECAY_HPP
#define TLPP_TYPE_TRAITS_DECAY_HPP

#include <Tlpp/TypeTraits/array_traits.hpp>
#include <Tlpp/TypeTraits/basic_traits.hpp>
#include <Tlpp/TypeTraits/conditional.hpp>
#include <Tlpp/TypeTraits/cv_traits.hpp>
#include <Tlpp/TypeTraits/pointer_traits.hpp>
#include <Tlpp/TypeTraits/ref_traits.hpp>

namespace tl
{
	namespace type_traits
	{
		template<typename T>
		struct decay
		{
		private:
			using U1 = remove_reference_t<T>;
			using U2 = conditional_t<is_function_v<U1>,
			                         add_pointer_t<U1>,
			                         remove_cv_t<U1>>;

		public:
			using type = conditional_t<is_array_v<U1>,
			                           add_pointer_t<remove_extent_t<U1>>,
			                           U2>;
		};

		template<typename T>
		using decay_t = typename decay<T>::type;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_DECAY_HPP