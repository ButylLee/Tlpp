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

		enum class InfoType
		{
			Info,
			Error
		};

		class Test : Statical
		{
		public:
#ifdef TLPP_MSVC
			static int RunAndDispose(int argc, wchar_t* argv[]);
#else
			static int RunAndDispose(int argc, char* argv[]);
#endif

			static void RegisterTestCase(const wchar_t* file,
			                             const wchar_t* info,
			                             bool is_category,
			                             TestFuncType func);

			static void PrintInfo(const wchar_t* info, InfoType type);
		};


#define TEST_CATEGORY(INFO)                                                         \
	void CONCAT(TEST_CATEGORY_FUNC_, __LINE__)();                                   \
	static const int CONCAT(TEST_CATEGORY_, __LINE__) =                             \
		(::tl::test::Test::RegisterTestCase(                                        \
			 WIDEN(__FILE__),                                                       \
			 WIDEN(INFO),                                                           \
			 true,                                                                  \
			 &CONCAT(TEST_CATEGORY_FUNC_, __LINE__)),                               \
	     0);                                                                        \
	void CONCAT(TEST_CATEGORY_FUNC_, __LINE__)()

#define TEST_CASE(INFO)                                                             \
	void CONCAT(TEST_CASE_FUNC_, __LINE__)();                                       \
	static const int CONCAT(TEST_CASE_, __LINE__) =                                 \
		(::tl::test::Test::RegisterTestCase(WIDEN(__FILE__),                        \
	                                        WIDEN(INFO),                            \
	                                        false,                                  \
	                                        &CONCAT(TEST_CASE_FUNC_, __LINE__)),    \
	     0);                                                                        \
	void CONCAT(TEST_CASE_FUNC_, __LINE__)()

#define TEST_ASSERT(STATEMENT)                                                      \
	do                                                                              \
	{                                                                               \
		if (!(STATEMENT))                                                           \
			throw ::tl::test::TestAssertException(                                  \
				L"Test Assert Failed: " QUOTE(STATEMENT));                          \
	} while (false)

#define TEST_PRINT(INFO)                                                            \
	::tl::test::Test::PrintInfo((INFO), tl::test::InfoType::Info)

	} // namespace test
} // namespace tl

#include <Tlpp/Test/TestTools.hpp>
#include <Tlpp/Test/impl/Test.impl.hpp>

#endif // TLPP_TEST_HPP