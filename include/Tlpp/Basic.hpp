#ifndef TLPP_BASIC_HPP
#define TLPP_BASIC_HPP

#include <Tlpp/Config.h>

#ifndef TLPP_MSVC
#include <cstdint>
#endif

namespace tl
{
#ifdef TLPP_MSVC
	using tint8_t = signed __int8;
	using tuint8_t = unsigned __int8;
	using tint16_t = signed __int16;
	using tuint16_t = unsigned __int16;
	using tint32_t = signed __int32;
	using tuint32_t = unsigned __int32;
	using tint64_t = signed __int64;
	using tuint64_t = unsigned __int64;
#else
	using tint8_t = int8_t;
	using tuint8_t = uint8_t;
	using tint16_t = int16_t;
	using tuint16_t = uint16_t;
	using tint32_t = int32_t;
	using tuint32_t = uint32_t;
	using tint64_t = int64_t;
	using tuint64_t = uint64_t;
#endif

#ifdef TLPP_64
	using tint = tint64_t;
	using tuint = tuint64_t;
#else
	using tint = tint32_t;
	using tuint = tuint32_t;
#endif

	class NotCopyable
	{
	protected:
		NotCopyable() = default;
		~NotCopyable() = default;
		NotCopyable(const NotCopyable&) = delete;
		NotCopyable& operator=(const NotCopyable&) = delete;
	};

	class Statical
	{
	protected:
		Statical() = delete;
	};

	class Object
	{
	public:
		virtual ~Object() = default;
	};

	class Interface : NotCopyable
	{
	public:
		virtual ~Interface() = default;
	};

	class Error
	{
	public:
		Error() = default;

		Error(const wchar_t* message_) noexcept
			: message(message_)
		{}

		[[nodiscard]] const wchar_t* what() const noexcept
		{
			return message;
		}

	private:
		const wchar_t* message = nullptr;
	};

} // namespace tl

#endif // TLPP_BASIC_HPP