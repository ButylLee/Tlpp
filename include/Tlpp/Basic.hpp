#ifndef TLPP_BASIC_HPP
#define TLPP_BASIC_HPP

class NotCopyable
{
protected:
	NotCopyable() = default;
	~NotCopyable() = default;
	NotCopyable(const NotCopyable&) = delete;
	NotCopyable& operator=(const NotCopyable&) = delete;
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

#endif // TLPP_BASIC_HPP