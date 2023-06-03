#include "stdafx.h"
#include "RequestHandlerException.h"

RequestHandlerException::RequestHandlerException() : m_sErrorLocation{},  exception()
{
}

RequestHandlerException::RequestHandlerException(const char* sMessage, const char* errorLocation = __FILE__ + __LINE__) : exception(sMessage)
{
}

RequestHandlerException::~RequestHandlerException()
{
}

const char* RequestHandlerException::what() const
{
    
    return nullptr;
}
