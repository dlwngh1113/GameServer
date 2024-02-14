#include "stdafx.h"
#include "BaseCommandHandlerFactory.h"
#include "BaseCommandHandler.h"

namespace Core
{
	BaseCommandHandlerFactory::BaseCommandHandlerFactory() : IHandlerFactory()
	{
	}

	BaseCommandHandlerFactory::~BaseCommandHandlerFactory()
	{
	}

	shared_ptr<BaseCommandHandler> BaseCommandHandlerFactory::Create(short type)
	{
		ICreator<BaseCommandHandler>* creator = GetCreator(type);
		if (!creator)
			throw exception{ "해당 요청을 처리할 수 있는 Creator가 존재하지 않습니다. request = " + type };

		shared_ptr<BaseCommandHandler> handler = creator->Create();

		if (handler == nullptr)
			throw exception{ "핸들러가 없습니다." };

		return handler;
	}
}