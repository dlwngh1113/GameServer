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

	std::shared_ptr<BaseCommandHandler> BaseCommandHandlerFactory::Create(short type)
	{
		ICreator<BaseCommandHandler>* creator = GetCreator(type);
		if (!creator)
			throw std::exception{ "�ش� ��û�� ó���� �� �ִ� Creator�� �������� �ʽ��ϴ�. request = " + type };

		std::shared_ptr<BaseCommandHandler> handler = creator->Create();

		if (handler == nullptr)
			throw std::exception{ "�ڵ鷯�� �����ϴ�." };

		return handler;
	}
}