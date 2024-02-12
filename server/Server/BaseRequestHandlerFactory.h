#pragma once
#include "IHandlerFactory.h"

namespace Core
{
	class BaseRequestHandlerFactory : public IHandlerFactory
	{
	public:
		BaseRequestHandlerFactory();
		virtual ~BaseRequestHandlerFactory();

		virtual shared_ptr<BaseRequestHandler> Create(short type) override;
		virtual void Initialize() = 0;
	};
}
