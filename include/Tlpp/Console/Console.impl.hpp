#ifndef TLPP_CONSOLE_IMPL_HPP
#define TLPP_CONSOLE_IMPL_HPP

#include "Config.h"

#ifdef TLPP_WIN
#include <Windows.h>
#else
#include <cstdio>
#endif

namespace tl
{
	namespace console
	{
		inline void Console::Write(const char* string)
		{
		}

		inline void Console::WriteLine(const char* string)
		{
		}

		inline void Console::Read()
		{
		}

		inline void Console::SetTitle()
		{
#ifdef TLPP_WIN

#endif
		}

		inline void Console::SetColor()
		{
#ifdef TLPP_WIN

#else

#endif
		}

	} // namespace console
} // namespace tl

#endif // TLPP_CONSOLE_IMPL_HPP