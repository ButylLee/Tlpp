#ifndef TLPP_BASIC_HPP
#define TLPP_BASIC_HPP

namespace tl
{
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

} // namespace tl

#endif // TLPP_BASIC_HPP