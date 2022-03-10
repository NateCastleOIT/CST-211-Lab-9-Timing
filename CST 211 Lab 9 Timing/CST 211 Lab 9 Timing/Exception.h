#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <ostream>
#include <string>
#include <exception>
using std::ostream;
using std::string;
using std::exception;

class Exception : virtual public std::exception
{
private:
	string m_msg;
public:
	Exception() : m_msg("") {};
	~Exception();
	Exception(const string msg);
	Exception(const Exception& copy);
	Exception(Exception&& copy) noexcept;
	Exception& operator = (const Exception& rhs);
	Exception& operator = (Exception&& rhs) noexcept;
	const string getMessage() const;
	void setMessage(const string msg);
	friend ostream& operator << (ostream& stream, const Exception& except);
};

Exception::~Exception()
{
	m_msg = "";
}

Exception::Exception(const string msg)
{
	this->setMessage(msg);
}

Exception::Exception(const Exception& copy)
{
	m_msg = copy.m_msg;
}

Exception::Exception(Exception&& copy) noexcept
{
	m_msg = copy.m_msg;
	copy.m_msg = "";
}

Exception& Exception::operator=(const Exception& rhs)
{
	if (this != &rhs) {
		if (rhs.m_msg != "")
			m_msg = rhs.m_msg;
	}
	return *this;
}

Exception& Exception::operator=(Exception&& rhs) noexcept
{
	if (this != &rhs) {
		if (rhs.m_msg != "")
			m_msg = rhs.m_msg;
	}
	rhs.m_msg = "";				// set rhs to "" for move copy
	return *this;
}

const string Exception::getMessage() const
{
	return m_msg;
}

void Exception::setMessage(const string msg)
{
	m_msg = msg;
}

ostream& operator<<(ostream& stream, const Exception& except)
{
	stream << except;
	return stream;
}
#endif EXCEPTION_H