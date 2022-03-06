#ifndef TLPP_TYPE_TRAITS_TYPE_IDENTITY_HPP
#define TLPP_TYPE_TRAITS_TYPE_IDENTITY_HPP

namespace tl
{
	namespace type_traits
	{
		template<typename T>
		struct type_identity
		{
			using type = T;
		};

		template<typename T>
		using type_identity_t = typename type_identity<T>::type;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_TYPE_IDENTITY_HPP