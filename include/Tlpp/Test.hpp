#ifndef TLPP_TEST_HPP
#define TLPP_TEST_HPP

#include "Macro.h"
#include <stdio.h>

#define TEST(NAME)                                                                                                     \
	void CONCAT(test_method_, NAME)();                                                                                 \
	struct CONCAT(test_class_, NAME)                                                                                   \
	{                                                                                                                  \
		CONCAT(test_class_, name)()                                                                                    \
		{                                                                                                              \
			printf_s("----------- TEST ");                                                                             \
			printf_s(QUOTE(NAME));                                                                                     \
			printf_s(" -----------\n");                                                                                \
			CONCAT(test_method_, NAME)();                                                                              \
			printf_s("\n");                                                                                            \
		}                                                                                                              \
	} CONCAT(test_object_, NAME);                                                                                      \
	void CONCAT(test_method_, NAME)()

#endif // TLPP_TEST_HPP