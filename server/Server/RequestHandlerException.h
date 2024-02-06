#pragma once

#define LogFile "[" + std::string(__FILE__) + ":" + std::to_string(__LINE__) + "] - "

namespace Core
{
	class RequestHandlerException : public std::exception
	{
		std::string m_sErrorLog;
	public:
		explicit RequestHandlerException();
		explicit RequestHandlerException(const std::string& sLogFile, const char* sMessage);
		virtual ~RequestHandlerException();

		_NODISCARD virtual const char* what() const override;
	};
}