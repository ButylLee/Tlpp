#ifndef TLPP_TEST_HPP
#define TLPP_TEST_HPP

#include <Tlpp/Basic.hpp>
#include <Tlpp/Config.h>
#include <Tlpp/Macro.h>

// TODO:TEST_ASSERT & TEST_CHECK that throw Error
namespace tl
{
	namespace test
	{
		using TestFuncType = void (*)();

		class Test : Statical
		{
		public:
#ifdef TLPP_MSVC
			static int RunAndDispose(int argc, wchar_t* argv[])
#else
			static int RunAndDispose(int argc, char* argv[])
#endif
			{
				return 0;
			}

			static void RegisterTestCase(const wchar_t* file,
			                             const wchar_t* info,
			                             bool is_category,
			                             TestFuncType func)
			{}
		};


#define TEST_CATEGORY(INFO)                                                         \
	void CONCAT(TEST_CATEGORY_FUNC_, __LINE__)();                                   \
	static ::tl::test::TestCase CONCAT(TEST_CATEGORY_, __LINE__)(                   \
		WIDEN(__FILE__),                                                            \
		WIDEN(INFO),                                                                \
		true,                                                                       \
		&CONCAT(TEST_CATEGORY_FUNC_, __LINE__));                                    \
	void CONCAT(TEST_CATEGORY_FUNC_, __LINE__)()

#define TEST_CASE(INFO)                                                             \
	void CONCAT(TEST_CASE_FUNC_, __LINE__)();                                       \
	static ::tl::test::TestCase CONCAT(TEST_CASE_, __LINE__)(                       \
		WIDEN(__FILE__),                                                            \
		WIDEN(INFO),                                                                \
		false,                                                                      \
		&CONCAT(TEST_CASE_FUNC_, __LINE__));                                        \
	void CONCAT(TEST_CASE_FUNC_, __LINE__)()

#define TEST_ASSERT(STATEMENT)                                                      \
	do                                                                              \
	{                                                                               \
		if (!(STATEMENT))                                                           \
			throw ::tl::test::TestAssertException(                                  \
				L"Test Assert Failed: " QUOTE(STATEMENT));                          \
	} while (false)

	} // namespace test
} // namespace tl

#include <Tlpp/Test/TestTools.hpp>
#include <Tlpp/Test/impl/Test.impl.hpp>

#endif // TLPP_TEST_HPP