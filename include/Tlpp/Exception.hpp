#ifndef TLPP_EXCEPTION_HPP
#define TLPP_EXCEPTION_HPP

#include "Basic.hpp"
#include "Config.h"
#include <string>  //TODO:remove
#include <utility> //TODO:remove

#ifdef TLPP_WIN
#include <Windows.h>
#endif

namespace tl
{
	class Exception : public Object
	{
	public:
		[[nodiscard]] virtual const wchar_t* what() const noexcept = 0;
	};

	class RuntimeException : public Exception
	{
	public:
		explicit RuntimeException(std::wstring message) noexcept
			: buffer(std::move(message))
		{}

		[[nodiscard]] const wchar_t* what() const noexcept override
		{
			return buffer.c_str();
		}

	private:
		std::wstring buffer;
	};

#ifdef TLPP_WIN
	class Win32Exception : public Exception
	{
	public:
		using CodeType = decltype(GetLastError());

		explicit Win32Exception(CodeType error_code = GetLastError()) noexcept
			: code(error_code)
		{
			if (!format())
			{
				buffer = L"Format Error Message Failed.";
				code = CodeType{};
			}
		}

		~Win32Exception() noexcept
		{
			if (code != CodeType{})
				LocalFree((HLOCAL)buffer);
			buffer = nullptr;
		}

		Win32Exception(const Win32Exception& other) noexcept
			: Win32Exception(other.code)
		{}

		Win32Exception& operator=(const Win32Exception& other) noexcept
		{
			if (this != &other)
				rebuild(other.code);
			return *this;
		}

	public:
		[[nodiscard]] const wchar_t* what() const noexcept override
		{
			return buffer;
		}

	private:
		bool format() noexcept
		{
			return static_cast<bool>(FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			                                            FORMAT_MESSAGE_IGNORE_INSERTS,
			                                        NULL,
			                                        code,
			                                        LANG_USER_DEFAULT,
			                                        (LPWSTR)&buffer,
			                                        0,
			                                        NULL));
		}
		void rebuild(CodeType error_code) noexcept
		{
			this->~Win32Exception();
			(void)new (this) Win32Exception(error_code);
		}

	private:
		const wchar_t* buffer = nullptr;
		CodeType code = {};
	};
#endif // TLPP_WIN

} // namespace tl

#endif // TLPP_EXCEPTION_HPP