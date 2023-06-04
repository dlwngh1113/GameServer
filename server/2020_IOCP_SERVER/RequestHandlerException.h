#pragma once

class RequestHandlerException : public std::exception
{
	std::string m_sErrorLog;
public:
	explicit RequestHandlerException();
	explicit RequestHandlerException(const char* sMessage, const char* sFile = __FILE__, const int nFileLine = __LINE__);
	virtual ~RequestHandlerException();

	_NODISCARD virtual const char* what() const override;
};
