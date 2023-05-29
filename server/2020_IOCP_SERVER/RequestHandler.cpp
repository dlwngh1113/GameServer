#include "stdafx.h"
#include "RequestHandler.h"
#include "CServer.h"

void RequestHandler::Handle()
{
	m_user = CServer::GetInstance().GetUser(m_peer->GetID());

	if (m_user == nullptr)
		throw std::exception{ "해당 유저가 존재하지 않습니다." };

	HandleRequest();
}
