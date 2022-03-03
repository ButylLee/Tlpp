#ifndef TLPP_TYPE_TRAITS_DECAY_HPP
#define TLPP_TYPE_TRAITS_DECAY_HPP

namespace tl
{
	namespace type_traits
	{
		template<typename T>
		struct decay
		{

		};

		template<typename T>
		using decay_t = typename decay<T>::type;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_DECAY_HPP