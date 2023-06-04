#include "stdafx.h"
#include "RequestHandlerException.h"

RequestHandlerException::RequestHandlerException() : m_sErrorLog{},  exception()
{
}

RequestHandlerException::RequestHandlerException(const char* sMessage, const char* sFile, const int nFileLine) : exception()
{
    m_sErrorLog = "[" + std::string(sFile) + " : " + std::to_string(nFileLine) + "] - ";
    m_sErrorLog += sMessage;
}

RequestHandlerException::~RequestHandlerException()
{
}

const char* RequestHandlerException::what() const
{
    return m_sErrorLog.c_str();
}
