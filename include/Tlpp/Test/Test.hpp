#ifndef TLPP_TEST_HPP
#define TLPP_TEST_HPP

#include <Tlpp/Basic.hpp>
#include <Tlpp/Config.h>
#include <Tlpp/Macro.h>
#include <Tlpp/Test/TestException.hpp>

#include <functional>

namespace tl
{
	namespace test
	{
		enum class MsgType
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
				const wchar_t* message = nullptr;
				std::function<void()> func;
				bool standalone_case = false;
				CategoryNode* next = nullptr;
			};
			struct TestInfo
			{
				const wchar_t* file = nullptr;
				const wchar_t* message = nullptr;
			};
			inline static bool has_run = false;

			static void Register(const wchar_t* file,
			                     const wchar_t* message,
			                     std::function<void()> func,
			                     bool standalone_case = false);

			static void Run();

			// Used in macro TEST_CATEGORY
			static TestInfo Register(const wchar_t* file, const wchar_t* message);
			template<typename TCallback>
			friend int operator+(TestInfo info, TCallback callback);

		private:
			inline static CategoryNode* category_head = nullptr;
			inline static CategoryNode** category_tail = &category_head;
		};

		class TestCase : Statical
		{
		public:
			using TestFuncType = void (*)();
			struct TestInfo
			{
				const wchar_t* file = nullptr;
				const wchar_t* message = nullptr;
			};

			static void
			Run(const wchar_t* file, const wchar_t* message, TestFuncType func);

			// Used in macro TEST_CASE
			static TestInfo Register(const wchar_t* file, const wchar_t* message);
			friend int operator+(TestInfo info, TestFuncType func);
		};

		class Test : Statical
		{
		public:
#ifdef TLPP_MSVC
			static int RunAndDispose(int argc, wchar_t* argv[]);
#else
			static int RunAndDispose(int argc, char* argv[]);
#endif

			static void PrintMessage(const wchar_t* message, MsgType type);
		};


#define TEST_CATEGORY(INFO)                                                         \
	static const int CONCAT(TEST_CATEGORY_, __LINE__) =                             \
		::tl::test::TestCategory::Register(                                         \
			WIDEN(__FILE__ ": line " QUOTE(__LINE__)),                              \
			WIDEN(INFO)) +                                                          \
		[]() -> void

#define TEST_CASE(INFO)                                                             \
	static const int CONCAT(TEST_CASE_, __LINE__) =                                 \
		::tl::test::TestCase::Register(WIDEN(__FILE__ ": line " QUOTE(__LINE__)),   \
	                                   WIDEN(INFO)) +                               \
		[]() -> void

#define TEST_ASSERT(STATEMENT)                                                      \
	do                                                                              \
	{                                                                               \
		if (!(STATEMENT))                                                           \
			throw ::tl::test::TestAssertException(                                  \
				L"Test Assert Failed: " QUOTE(STATEMENT));                          \
	} while (false)

#define TEST_PRINT(INFO)                                                            \
	::tl::test::Test::PrintMessage((INFO), tl::test::MsgType::Info)

	} // namespace test
} // namespace tl

#include <Tlpp/Test/impl/Test.impl.hpp>

#endif // TLPP_TEST_HPP