#include "stdafx.h"
#include "RequestHandler.h"
#include "CServer.h"

void RequestHandler::Handle()
{
	m_user = CServer::GetInstance().GetUser(m_peer->GetID());

	if (m_user == nullptr)
		throw RequestHandlerException{ "�ش� ������ �������� �ʽ��ϴ�." };

	HandleRequest();
}
