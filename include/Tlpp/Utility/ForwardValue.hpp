#ifndef TLPP_UTILITY_FORWARD_VALUE_HPP
#define TLPP_UTILITY_FORWARD_VALUE_HPP

#include <Tlpp/TypeTraits/ref_traits.hpp>

namespace tl
{
	namespace utility
	{
		template<typename T>
		[[nodiscard]] constexpr T&&
		ForwardValue(type_traits::remove_reference_t<T>& val) noexcept
		{
			return static_cast<T&&>(val);
		}

		template<typename T>
		[[nodiscard]] constexpr T&&
		ForwardValue(type_traits::remove_reference_t<T>&& val) noexcept
		{
			static_assert(!type_traits::is_lvalue_reference_v<T>,
			              "bad Forward call.");
			return static_cast<T&&>(val);
		}

	} // namespace utility
	using utility::ForwardValue;
} // namespace tl

#endif // TLPP_UTILITY_FORWARD_VALUE_HPP