#ifndef TLPP_TYPE_TRAITS_CONDITIONAL_HPP
#define TLPP_TYPE_TRAITS_CONDITIONAL_HPP

namespace tl
{
	namespace type_traits
	{
		template<bool B, typename T, typename F>
		struct conditional
		{
			using type = F;
		};

		template<typename T, typename F>
		struct conditional<true, T, F>
		{
			using type = T;
		};

		template<bool B, typename T, typename F>
		using conditional_t = typename conditional<B, T, F>::type;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_CONDITIONAL_HPP