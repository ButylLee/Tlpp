#ifndef TLPP_TEST_HPP
#define TLPP_TEST_HPP

#include "../Macro.h"
#include "Error.hpp"
#include <stdio.h>
// TODO:TEST_ASSERT & TEST_CHECK that throw Error
namespace tl
{
	namespace test
	{
		class Test
		{
		public:
			Test() = delete;

			using TestFuncType = void (*)();

			static void RunAndDispose(int argc, char* argv[])
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

#endif // TLPP_TEST_HPP