#ifndef TLPP_TEST_HPP
#define TLPP_TEST_HPP

#include <Tlpp/Basic.hpp>
#include <Tlpp/Config.h>
#include <Tlpp/Macro.h>

#include <cstdio>
// TODO:TEST_ASSERT & TEST_CHECK that throw Error
namespace tl
{
	namespace test
	{
		class Test : Statical
		{
		public:
			using TestFuncType = void (*)();

#ifdef TLPP_MSVC
			static void RunAndDispose(int argc, wchar_t* argv[])
#else
			static void RunAndDispose(int argc, char* argv[])
#endif
			{}
			static void RegisterTestCase(TestFuncType func)
			{}
		};


#define TEST(NAME)                                                                  \
	void CONCAT(test_case_method_, NAME)();                                         \
	struct CONCAT(test_case_class_, NAME)                                           \
	{                                                                               \
		CONCAT(test_case_class_, NAME)()                                            \
		{                                                                           \
			::tl::test::Test::RegisterTestCase(&CONCAT(test_case_method_, NAME));   \
			printf_s("----------- TEST ");                                          \
			printf_s(QUOTE(NAME));                                                  \
			printf_s(" -----------\n");                                             \
			CONCAT(test_case_method_, NAME)();                                      \
			printf_s("\n");                                                         \
		}                                                                           \
	} CONCAT(test_case_object_, NAME);                                              \
	void CONCAT(test_case_method_, NAME)()

	} // namespace test
} // namespace tl

#include <Tlpp/Test/Test.impl.hpp>

#endif // TLPP_TEST_HPP