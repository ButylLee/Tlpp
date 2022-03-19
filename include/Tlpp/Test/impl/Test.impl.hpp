#ifndef TLPP_TEST_IMPL_HPP
#define TLPP_TEST_IMPL_HPP

#include <Tlpp/Basic.hpp>
#include <Tlpp/Console/Console.hpp>
#include <Tlpp/Exception.hpp>
#include <Tlpp/Test/TestException.hpp>

#include <cwchar>
#include <string> //TODO:remove

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

	inline int TestCategory::Run()
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

		bool is_passed = passed_files == total_files;
		MsgType msg_type = is_passed ? MsgType::Case : MsgType::Error;
		Test::PrintMessage(L"-------------------------", MsgType::Regular);
		Test::PrintMessage(
			L" Test File: " + std::to_wstring(TestCategory::passed_files) + L"/" +
				std::to_wstring(TestCategory::total_files) + L" passed",
			msg_type);
		Test::PrintMessage(L"-------------------------", MsgType::Regular);
		Test::PrintMessage(L" Test Case: " +
		                       std::to_wstring(TestCase::passed_cases) + L"/" +
		                       std::to_wstring(TestCase::total_cases) + L" passed",
		                   msg_type);
		Test::PrintMessage(L"-------------------------", MsgType::Regular);
		return is_passed ? 0 : 1;
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
			// wrap single test case as a category
			TestCategory::Register(
				file,
				message,
				[=] { ::tl::test::TestCase::Run(file, message, func); },
				true);
		}
		else // run the test case
		{
			if (Test::suppress_failure)
			{
				try
				{
					func();
				}
				catch (const TestAssertException& e)
				{
					RecordFailure(e.what());
				}
				catch (const TestDeployException& e)
				{
					RecordFailure(e.what());
				}
				catch (const Error& e)
				{
					RecordFailure(e.what());
				}
				catch (const Exception& e)
				{
					RecordFailure(e.what());
				}
				catch (...)
				{
					RecordFailure(L"Unknown Test Failure occurred.");
				}
			}
			else
			{
				func();
			}
		}
	}

	inline void TestCase::RecordFailure(const wchar_t* message)
	{
		Test::PrintMessage(message, MsgType::Error);
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
		do
		{
			if (argc <= 2)
			{
				if (argc == 2)
				{
#ifdef TLPP_MSVC
					std::wstring cmd = argv[1];
#else
					// TODO
#endif
					if (cmd == L"-D")
					{
						Test::suppress_failure = false;
						Test::PrintMessage(L"Debug Mode is on.", MsgType::Info);
					}
					else
						break;
				}
				return TestCategory::Run();
			}
		} while (false);
		Test::PrintMessage(L"Command: [-D]", MsgType::Error);
		return 1;
	}

	inline void Test::PrintMessage(std::wstring info, MsgType type)
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