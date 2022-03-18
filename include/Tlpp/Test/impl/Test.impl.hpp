#ifndef TLPP_TEST_IMPL_HPP
#define TLPP_TEST_IMPL_HPP

#include <Tlpp/Console/Console.hpp>

#include <cwchar>

namespace tl::test
{
	inline void TestCategory::Register(const wchar_t* file,
	                                   const wchar_t* message,
	                                   std::function<void()> func,
	                                   bool standalone_case)
	{
		auto* temp = new CategoryNode{file, message, func, standalone_case};
		*category_tail = temp;
		category_tail = &temp->next;
	}

	inline void TestCategory::Run()
	{
		has_run = true;
		auto* current = category_head;
		category_head = nullptr;
		while (current)
		{
			current->func();

			auto* temp = current;
			current = current->next;
			delete temp;
		}
	}

	inline TestCategory::TestInfo
	TestCategory::Register(const wchar_t* file, const wchar_t* message)
	{
		return {file, message};
	}

	template<typename TCallback>
	inline int operator+(TestCategory::TestInfo info, TCallback callback)
	{
		::tl::test::TestCategory::Register(info.file, info.message, callback);
		return 1;
	}

	inline void
	TestCase::Run(const wchar_t* file, const wchar_t* message, TestFuncType func)
	{
		if (!TestCategory::has_run)
		{
			TestCategory::Register(
				file,
				message,
				[=] { ::tl::test::TestCase::Run(file, message, func); },
				true);
		}
		else
		{
			func();
		}
	}

	inline TestCase::TestInfo
	TestCase::Register(const wchar_t* file, const wchar_t* message)
	{
		return {file, message};
	}

	inline int operator+(TestCase::TestInfo info, TestCase::TestFuncType func)
	{
		::tl::test::TestCase::Run(info.file, info.message, func);
		return 1;
	}

#ifdef TLPP_MSVC
	inline int Test::RunAndDispose(int argc, wchar_t* argv[])
#else
	inline int Test::RunAndDispose(int argc, char* argv[])
#endif
	{
		TestCategory::Run();
		return 0;
	}

	inline void Test::PrintMessage(const wchar_t* info, MsgType type)
	{
		using namespace console;
		using enum MsgType;
		switch (type)
		{
		case Regular:
			Console::SetColor(true, true, true, false); // White
			break;
		case Info:
			Console::SetColor(false, false, true, true); // Bright Blue
			break;
		case Error:
			Console::SetColor(true, false, false, false); // Red
			break;
		case Category:
			Console::SetColor(false, true, true, true); // Bright Aqua
			break;
		case Case:
			Console::SetColor(false, true, false, false); // Green
			break;
		}
		Console::WriteLine(info);
		Console::SetDefaultColor();
	}

} // namespace tl::test

#endif // TLPP_TEST_IMPL_HPP