#ifndef TLPP_TEST_HPP
#define TLPP_TEST_HPP

#include <Tlpp/Basic.hpp>
#include <Tlpp/Config.h>
#include <Tlpp/Macro.h>
#include <Tlpp/Test/TestException.hpp>

#include <cwchar>
#include <functional>

namespace tl
{
	namespace test
	{
		using TestFuncType = void (*)();

		enum class InfoType
		{
			Regular,
			Info,
			Error,
			Category,
			Case,
		};

		class TestCategory : Statical
		{
		public:
			struct CategoryNode
			{
				const wchar_t* file = nullptr;
				const wchar_t* info = nullptr;
				std::function<void()> func;
				bool standalone_case = false;
				CategoryNode* next = nullptr;
			};
			inline static CategoryNode* category_head = nullptr;
			inline static CategoryNode** category_tail = &category_head;
			inline static bool has_run = false;

			static void Register(const wchar_t* file,
			                     const wchar_t* info,
			                     std::function<void()> func,
			                     bool standalone_case = false)
			{
				auto* temp = new CategoryNode{file, info, func, standalone_case};
				*category_tail = temp;
				category_tail = &temp->next;
			}

			static void Run()
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
		};

		class TestCase : Statical
		{
		public:
			static void
			Run(const wchar_t* file, const wchar_t* info, TestFuncType func)
			{
				if (!TestCategory::has_run)
				{
					TestCategory::Register(
						file,
						info,
						[=] { ::tl::test::TestCase::Run(file, info, func); },
						true);
				}
				else
				{
					func();
				}
			}
		};

		class Test : Statical
		{
		public:
#ifdef TLPP_MSVC
			static int RunAndDispose(int argc, wchar_t* argv[]);
#else
			static int RunAndDispose(int argc, char* argv[]);
#endif

			static void PrintInfo(const wchar_t* info, InfoType type);
		};


#define TEST_CATEGORY(INFO)                                                         \
	void CONCAT(TEST_CATEGORY_FUNC_, __LINE__)();                                   \
	static const int CONCAT(TEST_CATEGORY_, __LINE__) =                             \
		(::tl::test::TestCategory::Register(                                        \
			 WIDEN(__FILE__),                                                       \
			 WIDEN(INFO),                                                           \
			 &CONCAT(TEST_CATEGORY_FUNC_, __LINE__)),                               \
	     0);                                                                        \
	void CONCAT(TEST_CATEGORY_FUNC_, __LINE__)()

#define TEST_CASE(INFO)                                                             \
	void CONCAT(TEST_CASE_FUNC_, __LINE__)();                                       \
	static const int CONCAT(TEST_CASE_, __LINE__) =                                 \
		(::tl::test::TestCase::Run(WIDEN(__FILE__),                                 \
	                               WIDEN(INFO),                                     \
	                               &CONCAT(TEST_CASE_FUNC_, __LINE__)),             \
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

#include <Tlpp/Test/impl/Test.impl.hpp>

#endif // TLPP_TEST_HPP