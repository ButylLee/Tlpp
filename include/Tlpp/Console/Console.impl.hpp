#ifndef TLPP_CONSOLE_IMPL_HPP
#define TLPP_CONSOLE_IMPL_HPP

#include <Tlpp/Config.h>
#include <Tlpp/Exception.hpp>

#include <cwchar>

#ifdef TLPP_WIN
#include <Windows.h>
#else
#include <cstdio>
#include <iostream>
#endif

namespace tl::console
{
	inline void Console::Write(const wchar_t* string, tint length)
	{
#ifdef TLPP_WIN
		HANDLE ouput_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD written = 0;
		DWORD mode = 0;
		if (GetFileType(ouput_handle) & FILE_TYPE_CHAR &&
		    GetConsoleMode(ouput_handle, &mode))
		{
			WriteConsoleW(ouput_handle, string, (DWORD)length, &written, NULL);
		}
		else // output_handle has been redirected
		{
			auto code_page = GetConsoleOutputCP();
			int count =
				WideCharToMultiByte(code_page, 0, string, -1, NULL, 0, NULL, NULL);
			char* buffer = new char[count];
			WideCharToMultiByte(code_page, 0, string, -1, buffer, count, NULL, NULL);
			WriteFile(ouput_handle, string, length, &written, NULL);
			delete[] buffer;
		}
#else
		wprintf_s(string);
#endif
	}

	inline void Console::Write(const wchar_t* string)
	{
		Write(string, wcslen(string));
	}

	inline void Console::WriteLine(const wchar_t* string)
	{
		Write(string);
		Write(L"\n");
	}

	inline std::wstring Console::Read()
	{
#ifdef TLPP_WIN
		HANDLE input_handle = GetStdHandle(STD_INPUT_HANDLE);
		std::wstring string;
		DWORD count = 0;
		wchar_t ch;
		while (true)
		{
			ReadConsoleW(input_handle, &ch, 1, &count, NULL);
			if (ch == L'\n')
			{
				break;
			}
			else
			{
				string += ch;
			}
		}
		return string;
#else
		std::wstring string;
		std::getline(std::wcin, string);
		return string;
#endif
	}

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
#else

#endif
	}

	inline void Console::SetDefaultColor()
	{
		SetColor(true, true, true, false); // White
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
	inline HANDLE Console::GetOutputHandle()
	{
		static HANDLE handle =
			GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE
				? GetStdHandle(STD_OUTPUT_HANDLE)
				: throw Win32Exception{};
		return handle;
	}

	inline HANDLE Console::GetInputHandle()
	{
		static HANDLE handle = GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE
		                           ? GetStdHandle(STD_INPUT_HANDLE)
		                           : throw Win32Exception{};
		return handle;
	}

	inline HWND Console::GetConsoleHandle()
	{
		static HWND hwnd =
			GetConsoleWindow() != NULL
				? GetConsoleWindow()
				: throw RuntimeException(L"Failed to obtain Console Handle.");
		return hwnd;
	}
#endif

} // namespace tl::console

#endif // TLPP_CONSOLE_IMPL_HPP