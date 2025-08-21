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

	std::shared_ptr<BaseCommandHandler> BaseCommandHandlerFactory::Create(int16_t type)
	{
		ICreator<BaseCommandHandler>* creator = GetCreator(type);
		if (!creator)
			throw std::runtime_error{ std::format("해당 요청을 처리할 수 있는 Creator가 존재하지 않습니다. request = {}", type).c_str()};

		std::shared_ptr<BaseCommandHandler> handler = creator->Create();

		if (handler == nullptr)
			throw std::runtime_error{ "핸들러가 없습니다." };

		return handler;
	}
}