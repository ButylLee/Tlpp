#ifndef TLPP_CONSOLE_HPP
#define TLPP_CONSOLE_HPP

#include "Basic.hpp"

namespace tl
{
	namespace console
	{
		class Console : Statical
		{
			static void Write(const char* string);
			static void WriteLine(const char* string);

			static void Read();

			static void SetTitle();
			static void SetColor();
		};

	} // namespace console
} // namespace tl

#include "Console.impl.hpp"

#endif // TLPP_CONSOLE_HPP