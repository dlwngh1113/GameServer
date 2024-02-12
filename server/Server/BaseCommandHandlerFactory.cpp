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
			throw exception{ "�ش� ��û�� ó���� �� �ִ� Creator�� �������� �ʽ��ϴ�. request = " + type };

		shared_ptr<BaseCommandHandler> handler = creator->Create();

		if (handler == nullptr)
			throw exception{ "�ڵ鷯�� �����ϴ�." };

		return handler;
	}
}