#ifndef TLPP_TEST_IMPL_HPP
#define TLPP_TEST_IMPL_HPP

#include <Tlpp/Console/Console.hpp>

namespace tl::test
{
#ifdef TLPP_MSVC
	inline int Test::RunAndDispose(int argc, wchar_t* argv[])
#else
	inline int Test::RunAndDispose(int argc, char* argv[])
#endif
	{}

	inline void Test::RegisterTestCase(const wchar_t* file,
	                                   const wchar_t* info,
	                                   bool is_category,
	                                   TestFuncType func)
	{}

	inline void Test::PrintInfo(const wchar_t* info, InfoType type)
	{
		using namespace console;
		using enum InfoType;
		switch (type)
		{
		case Info:
			Console::SetColor(false, false, true, true); // Bright Blue
			break;
		case Error:
			Console::SetColor(true, false, false, false); // Red
			break;
		}
		Console::WriteLine(info);
		Console::SetDefaultColor();
	}

} // namespace tl::test

#endif // TLPP_TEST_IMPL_HPP