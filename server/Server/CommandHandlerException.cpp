#include "stdafx.h"
#include "CommandHandlerException.h"

namespace Core
{
    CommandHandlerException::CommandHandlerException() : m_sErrorLog{}, exception()
    {
    }

    CommandHandlerException::CommandHandlerException(const std::string& sLogFile, const char* sMessage) : exception()
    {
        m_sErrorLog = sLogFile;
        m_sErrorLog += sMessage;
    }

    CommandHandlerException::~CommandHandlerException()
    {
    }

    const char* CommandHandlerException::what() const
    {
        return m_sErrorLog.c_str();
    }
}