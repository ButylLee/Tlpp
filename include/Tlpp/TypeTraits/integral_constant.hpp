#ifndef TLPP_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define TLPP_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

namespace tl
{
	namespace type_traits
	{
		template<typename T, T val>
		struct integral_constant
		{
			using value_type = T;
			using type = integral_constant;

			static constexpr T value = val;

			constexpr operator value_type() const noexcept
			{
				return value;
			}
			constexpr value_type operator()() const noexcept
			{
				return value;
			}
		};

		template<bool B>
		using bool_constant = integral_constant<bool, B>;

		struct true_type : bool_constant<true>
		{};

		struct false_type : bool_constant<false>
		{};

	} // namespace type_traits
} // namespace tl

#endif // TLPP_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP