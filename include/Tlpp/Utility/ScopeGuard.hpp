/*
 *         <ScopeGuard>  By James Taylor(ButylLee)
 *                        2022/2/15
 *          https://github.com/ButylLee/ScopeGuard
 * ScopeGuard is a so-called Universal Resource Management
 * Class that employs RAII pattern. It provides a common way
 * of automatically releasing the resource acquired by the
 * users(programmer) via executing a provided callback when
 * leaving scope. Unlike smart pointer, ScopeGuard is not
 * taking charge of acquisition but release, referring to the
 * resources for which are too various to write control class
 * respectively, and users are supposed to acquire resource
 * first then bind it to ScopeGuard. It would operate when
 * exiting current scope by function return, exception throw, etc.
 *
 * NOTICE: You are NOT supposed to throw an exception or invoke
 * a throwing callable within ScopeGuard, if you did so, which
 * won't be prevented, the abort() will be called when sg operating.
 *
 * There are three ways to use ScopeGuard:
 *
 * (1) The recommended usage's as follows
 *
 *       -*-*-*-*-*-*-*-*-*-*-*-*-
 *       // acquire resource here
 *       finally{
 *           // release statment here
 *       };
 *       -*-*-*-*-*-*-*-*-*-*-*-*-
 *     You can put statments inside { } as in normal function
 *     body, they will be execute when exiting current scope.
 *
 * (2) Using this when you want to write lambda or pass function by yourself
 *
 *       -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 *       // acquire resource here
 *       INVOKE_ON_EXIT([&] { // release statment });
 *                      ^^^^lambda, function or executable object
 *       -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 *
 * (3) Using function MakeScopeGuard to create named variables so that you
 *     could apply ROLLBACK pattern or modify releasing(i.e. change the
 *     lifetime of ScopeGuard).
 *
 *       -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 *       // ROLLBACK pattern
 *       {
 *           auto sg = sg::MakeScopeGuard([&] { // release statment });
 *                                        ^^^^
 *                          lambda, function or executable object
 *
 *           // do something that may fail and throw exception
 *           sg.dismiss(); // if succeed, don't rollback
 *       }
 *
 *       // prolong or shorten the lifetime(barely use)
 *       auto prolong()
 *       {
 *           // acquire resource here
 *           auto sg = sg::MakeScopeGuard([&] { // release statment });
 *           return sg;
 *       }
 *       void shorten()
 *       {
 *           // acquire resource here
 *           auto sg = sg::MakeScopeGuard([&] { // release statment });
 *           foo(std::move(sg));
 *       }
 *       -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 */

#ifndef TLPP_UTILITY_SCOPE_GUARD_HPP
#define TLPP_UTILITY_SCOPE_GUARD_HPP

#include <Tlpp/Macro.h>
#include <Tlpp/TypeTraits/decay.hpp>
#include <Tlpp/TypeTraits/enable_if.hpp>
#include <Tlpp/TypeTraits/type_relationships.hpp>
#include <Tlpp/Utility/DeclVal.hpp>
#include <Tlpp/Utility/ForwardValue.hpp>
#include <Tlpp/Utility/MoveValue.hpp>

#define finally                                                                \
	auto CONCAT(ScopeGuard_Block_, __LINE__) =                                 \
		sg::detail::eSgFinally() + [&]() noexcept -> void
#define INVOKE_ON_EXIT(callback)                                               \
	auto CONCAT(ScopeGuard_, __LINE__) = sg::MakeScopeGuard(callback)

#include <type_traits>

namespace tl
{
	namespace sg
	{
		namespace detail
		{
			// Determining whether a type is a proper
			// callback that ScopeGuard need
			template<typename T>
			constexpr bool is_proper_callback_v =
				type_traits::is_same_v<void, decltype(utility::DeclVal<T>()())>;

			template<typename TCallback,
			         typename = type_traits::enable_if_t<
						 is_proper_callback_v<TCallback>>>
			class ScopeGuard;

			/* --- The helper functions provided multiple usages --- */
			enum class eSgFinally
			{}; // dummy

			template<typename TCallback>
			constexpr ScopeGuard<TCallback>
			operator+(eSgFinally, TCallback&& callback)
			{
				return ScopeGuard<TCallback>(ForwardValue<TCallback>(callback));
			}

			template<typename TCallback>
			constexpr ScopeGuard<TCallback> MakeScopeGuard(TCallback&& callback)
			{
				return ScopeGuard<TCallback>(ForwardValue<TCallback>(callback));
			}
			/* ----------------------------------------------------- */

			template<typename TCallback>
			class ScopeGuard<TCallback> final
			{
				using Callback = type_traits::decay_t<TCallback>;

				friend constexpr ScopeGuard<TCallback> operator+
					<TCallback>(eSgFinally, TCallback&&);
				friend constexpr ScopeGuard<TCallback>
				MakeScopeGuard<TCallback>(TCallback&&);

			private:
				explicit ScopeGuard(Callback callback)
					: m_callback(MoveValue(callback))
				{}

			public:
				~ScopeGuard() noexcept
				{
					if (m_active)
						m_callback();
				}

				ScopeGuard(ScopeGuard&& other) noexcept(
					std::is_nothrow_move_constructible_v<Callback>)
					: m_callback(MoveValue(other.m_callback))
					, m_active(MoveValue(other.m_active))
				{
					other.dismiss();
				}
				/* No move assign function */

				void dismiss() noexcept
				{
					m_active = false;
				}

				ScopeGuard(const ScopeGuard&) = delete;
				ScopeGuard& operator=(const ScopeGuard&) = delete;

			private:
				Callback m_callback;
				bool m_active = true;
			};
		} // namespace detail

		using detail::MakeScopeGuard;

	} // namespace sg
} // namespace tl

#endif // TLPP_UTILITY_SCOPE_GUARD_HPP