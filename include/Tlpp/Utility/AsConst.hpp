#ifndef TLPP_UTILITY_AS_CONST_HPP
#define TLPP_UTILITY_AS_CONST_HPP

#include <Tlpp/TypeTraits/cv_traits.hpp>

namespace tl
{
	namespace utility
	{
		template<typename T>
		constexpr type_traits::add_const_t<T>& AsConst(T& val) noexcept
		{
			return val;
		}

		template<typename T>
		void AsConst(const T&&) = delete;

	} // namespace utility
} // namespace tl

#endif // TLPP_UTILITY_AS_CONST_HPP