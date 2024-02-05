#include "stdafx.h"
#include "RequestHandlerException.h"

namespace Core
{
    RequestHandlerException::RequestHandlerException() : m_sErrorLog{}, exception()
    {
    }

    RequestHandlerException::RequestHandlerException(const std::string& sLogFile, const char* sMessage) : exception()
    {
        m_sErrorLog = sLogFile;
        m_sErrorLog += sMessage;
    }

    RequestHandlerException::~RequestHandlerException()
    {
    }

    const char* RequestHandlerException::what() const
    {
        return m_sErrorLog.c_str();
    }
}