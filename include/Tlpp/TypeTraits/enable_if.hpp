#ifndef TLPP_TYPE_TRAITS_ENABLE_IF_HPP
#define TLPP_TYPE_TRAITS_ENABLE_IF_HPP

namespace tl
{
	namespace type_traits
	{
		template<bool B, typename T = void>
		struct enable_if
		{};

		template<typename T>
		struct enable_if<true, T>
		{
			using type = T;
		};

		template<bool B, typename T = void>
		using enable_if_t = enable_if<B, T>;

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_ENABLE_IF_HPP