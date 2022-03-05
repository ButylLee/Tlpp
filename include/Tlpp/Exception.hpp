#ifndef TLPP_EXCEPTION_HPP
#define TLPP_EXCEPTION_HPP

#include <Tlpp/Basic.hpp>
#include <Tlpp/Config.h>
#include <Tlpp/Utility/MoveValue.hpp>

#include <string> //TODO:remove

#ifdef TLPP_WIN
#include <Tlpp/Utility/ScopeGuard.hpp>
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
			: buffer(tl::MoveValue(message))
		{}

		[[nodiscard]] const wchar_t* what() const noexcept override
		{
			return buffer.c_str();
		}

	private:
		std::wstring buffer;
	};

#ifdef TLPP_WIN
	class Win32Exception : public RuntimeException
	{
	public:
		using CodeType = decltype(GetLastError());

		explicit Win32Exception(CodeType error_code = GetLastError()) noexcept
			: Win32Exception("", error_code)
		{}

		explicit Win32Exception(std::wstring message,
		                        CodeType error_code = GetLastError()) noexcept
			: RuntimeException(format(message, error_code))
			, code(error_code)
		{}

	private:
		std::wstring format(std::wstring message, CodeType code) noexcept
		{
			const wchar_t* buffer = nullptr;
			finally
			{
				LocalFree((HLOCAL)buffer);
			}
			if (!static_cast<bool>(FormatMessageW(
					FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					code,
					LANG_USER_DEFAULT,
					(LPWSTR)&buffer,
					0,
					NULL)))
				return L"Format Error Message Failed.";
			return buffer + message;
		}

	private:
		CodeType code = {};
	};

	constexpr void ThrowWin32ExceptIf(bool condition, std::wstring message)
	{
		if (condition)
			throw Win32Exception(message);
	}

#endif // TLPP_WIN

} // namespace tl

#endif // TLPP_EXCEPTION_HPP