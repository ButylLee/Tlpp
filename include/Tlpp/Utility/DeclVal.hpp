#ifndef TLPP_UTILITY_DECLVAL_HPP
#define TLPP_UTILITY_DECLVAL_HPP

#include <Tlpp/TypeTraits/ref_traits.hpp>

namespace tl
{
	namespace utility
	{
		template<typename T>
		type_traits::add_rvalue_reference_t<T> DeclVal() noexcept;

	} // namespace utility
} // namespace tl

#endif // TLPP_UTILITY_DECLVAL_HPP