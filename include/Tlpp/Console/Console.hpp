#ifndef TLPP_CONSOLE_HPP
#define TLPP_CONSOLE_HPP

#include <Tlpp/Basic.hpp>
#include <Tlpp/Config.h>

#include <string> //TODO:remove

namespace tl
{
	namespace console
	{
		class Console : Statical
		{
		public:
			static void Write(const wchar_t* string, tint length);
			static void Write(const wchar_t* string);
			static void Write(std::wstring string);
			static void WriteLine(const wchar_t* string);
			static void WriteLine(std::wstring string);

			static std::wstring Read();

			static void SetTitle(const std::wstring& title);
			static void SetColor(bool red, bool green, bool blue, bool light);
			static void SetDefaultColor();
			static void SetCursorVisible(bool isVisible);

#ifdef TLPP_WIN
			static HANDLE GetOutputHandle();
			static HANDLE GetInputHandle();
			static HWND GetConsoleHandle();
#endif
		};

	} // namespace console
} // namespace tl

#include "Console.impl.hpp"

#endif // TLPP_CONSOLE_HPP