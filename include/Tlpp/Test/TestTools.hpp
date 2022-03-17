#ifndef TLPP_TEST_TEST_TOOLS_HPP
#define TLPP_TEST_TEST_TOOLS_HPP

#include <Tlpp/Exception.hpp>

namespace tl::test
{
	class TestAssertException : public RuntimeException
	{
		TestAssertException(const wchar_t* message)
			: RuntimeException(message)
		{}
	};

	class TestDeployException : public RuntimeException
	{
		TestDeployException(const wchar_t* message)
			: RuntimeException(message)
		{}
	};

} // namespace tl::test

#endif // TLPP_TEST_TEST_TOOLS_HPP