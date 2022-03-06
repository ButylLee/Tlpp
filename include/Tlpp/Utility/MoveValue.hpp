#ifndef TLPP_UTILITY_MOVE_VALUE_HPP
#define TLPP_UTILITY_MOVE_VALUE_HPP

#include <Tlpp/TypeTraits/conditional.hpp>
#include <Tlpp/TypeTraits/operation_traits.hpp>
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

		template<typename T>
		[[nodiscard]] constexpr type_traits::conditional_t<
			!type_traits::is_nothrow_move_constructible_v<T> &&
				type_traits::is_copy_constructible_v<T>,
			const T&,
			T&&>
		MoveValueIfNoexcept(T& val) noexcept
		{
			return MoveValue(val);
		}

	} // namespace utility
	using utility::MoveValue;
} // namespace tl

#endif // TLPP_UTILITY_MOVE_VALUE_HPP