#include <Tlpp/Test/Test.hpp>

TEST_CATEGORY("category1")
{
	TEST_CASE("case1")
	{
		TEST_PRINT(L"print1");
	};
	TEST_CASE("case2")
	{
		TEST_PRINT(L"print2");
	};
};

TEST_CATEGORY("category2")
{
	TEST_CASE("case3")
	{
		TEST_PRINT(L"print3");
	};
	TEST_CATEGORY("category2-1")
	{
		TEST_CASE("case4")
		{
			TEST_PRINT(L"print4");
		};
	};
};

TEST_CASE("case5")
{
	TEST_PRINT(L"print5");
};