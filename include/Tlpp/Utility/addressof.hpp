#ifndef TLPP_UTILITY_ADDRESSOF_HPP
#define TLPP_UTILITY_ADDRESSOF_HPP

namespace tl
{
	namespace utility
	{
		template<typename T>
		constexpr T* addressof(T& arg) noexcept
		{
			return reinterpret_cast<T*>(
				&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
		}

		template<typename T>
		const T* addressof(const T&&) = delete;

	} // namespace utility
} // namespace tl

#endif // TLPP_UTILITY_ADDRESSOF_HPP