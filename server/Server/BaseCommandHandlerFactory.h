#pragma once
#include "IHandlerFactory.h"

namespace Core
{
	class BaseCommandHandlerFactory : public IHandlerFactory
	{
	public:
		BaseCommandHandlerFactory();
		virtual ~BaseCommandHandlerFactory();

		virtual std::shared_ptr<BaseCommandHandler> Create(short type) override;
		virtual void Initialize() = 0;
	};
}
