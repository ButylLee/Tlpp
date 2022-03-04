#ifndef TLPP_CONSOLE_IMPL_HPP
#define TLPP_CONSOLE_IMPL_HPP

#include <Tlpp/Exception.hpp>
#include <Tlpp/Config.h>

#ifdef TLPP_WIN
#include <Windows.h>
#else
#include <cstdio>
#endif

namespace tl
{
	namespace console
	{
		inline void Console::Write(const wchar_t* string)
		{}

		inline void Console::WriteLine(const wchar_t* string)
		{}

		inline std::wstring Console::Read()
		{}

		inline void Console::SetTitle(const std::wstring& title)
		{
#ifdef TLPP_WIN
			if (!SetConsoleTitleW(title.c_str()))
				throw Win32Exception{};
#endif
		}

		inline void Console::SetColor(bool red, bool green, bool blue, bool light)
		{
#ifdef TLPP_WIN
			WORD color = 0;
			color |= red ? FOREGROUND_RED : 0;
			color |= green ? FOREGROUND_GREEN : 0;
			color |= blue ? FOREGROUND_BLUE : 0;
			color |= light ? FOREGROUND_INTENSITY : 0;
			if (!SetConsoleTextAttribute(GetOutputHandle(), color))
				throw Win32Exception{};
			if (!SetConsoleTextAttribute(GetInputHandle(), color))
				throw Win32Exception{};
#else

#endif
		}

		inline void Console::SetCursorVisible(bool isVisible)
		{
#ifdef TLPP_WIN
			CONSOLE_CURSOR_INFO cci;
			if (!GetConsoleCursorInfo(GetOutputHandle(), &cci))
				throw Win32Exception{};
			cci.bVisible = static_cast<BOOL>(isVisible);
			if (!SetConsoleCursorInfo(GetOutputHandle(), &cci))
				throw Win32Exception{};
#endif
		}

#ifdef TLPP_WIN
		inline HANDLE Console::GetOutputHandle() noexcept
		{
			static HANDLE handle =
				GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE
					? GetStdHandle(STD_OUTPUT_HANDLE)
					: throw Win32Exception{};
			return handle;
		}

		inline HANDLE Console::GetInputHandle() noexcept
		{
			static HANDLE handle =
				GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE
					? GetStdHandle(STD_INPUT_HANDLE)
					: throw Win32Exception{};
			return handle;
		}

		inline HWND Console::GetConsoleHandle() noexcept
		{
			static HWND hwnd =
				GetConsoleWindow() != NULL
					? GetConsoleWindow()
					: throw RuntimeException(L"Failed to obtain Console Handle.");
			return hwnd;
		}
#endif

	} // namespace console
} // namespace tl

#endif // TLPP_CONSOLE_IMPL_HPP