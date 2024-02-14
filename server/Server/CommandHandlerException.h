#pragma once

#define LogFile "[" + std::string(__FILE__) + ":" + std::to_string(__LINE__) + "] - "

namespace Core
{
	class CommandHandlerException : public std::exception
	{
		std::string m_sErrorLog;
	public:
		explicit CommandHandlerException();
		explicit CommandHandlerException(const std::string& sLogFile, const char* sMessage);
		virtual ~CommandHandlerException();

		_NODISCARD virtual const char* what() const override;
	};
}