#pragma once

#define ERROR_FORMAT __FILE__ + __LINE__

class RequestHandlerException : public std::exception
{
	std::string m_sErrorLocation;
public:
	explicit RequestHandlerException();
	explicit RequestHandlerException(const char* sMessage, const char* sErrorLocation = ERROR_FORMAT);
	virtual ~RequestHandlerException();

	_NODISCARD virtual const char* what() const override;
};
