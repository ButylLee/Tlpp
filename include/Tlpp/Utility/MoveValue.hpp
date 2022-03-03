#ifndef TLPP_UTILITY_MOVE_VALUE_HPP
#define TLPP_UTILITY_MOVE_VALUE_HPP

#include <Tlpp/TypeTraits/ref_traits.hpp>

namespace tl
{
	namespace utility
	{
		template<typename T>
		[[nodiscard]] constexpr type_traits::remove_reference_t<T>&&
		MoveValue(T&& val) noexcept
		{
			return static_cast<type_traits::remove_reference_t<T>&&>(val);
		}
	} // namespace utility
	using utility::MoveValue;
} // namespace tl

#endif // TLPP_UTILITY_MOVE_VALUE_HPP