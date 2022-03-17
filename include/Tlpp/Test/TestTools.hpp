#ifndef TLPP_TEST_TEST_TOOLS_HPP
#define TLPP_TEST_TEST_TOOLS_HPP

#include <Tlpp/Exception.hpp>

namespace tl
{
	namespace test
	{
		class TestCase
		{
		public:
			TestCase(const wchar_t* file,
			         const wchar_t* info,
			         bool is_category,
			         TestFuncType func)
			{
				Test::RegisterTestCase(file, info, is_category, func);
			}
		};

		class TestAssertException : public RuntimeException
		{
			TestAssertException(const wchar_t* message)
				: RuntimeException(message)
			{}
		};

	} // namespace test
} // namespace tl

#endif // TLPP_TEST_TEST_TOOLS_HPP