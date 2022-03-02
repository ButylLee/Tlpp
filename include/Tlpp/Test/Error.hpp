#ifndef TLPP_ERROR_HPP
#define TLPP_ERROR_HPP

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

#endif // TLPP_ERROR_HPP