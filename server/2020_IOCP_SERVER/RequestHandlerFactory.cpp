#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory()
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

RequestHandlerFactory* RequestHandlerFactory::GetInstance() const
{
	if (m_instance == nullptr)
		m_instance = new RequestHandlerFactory();

	return m_instance;
}
