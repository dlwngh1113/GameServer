#include "stdafx.h"
#include "LoginRequiredRequestHandler.h"
#include "User.h"
#include "Logger.h"

void LoginRequiredRequestHandler::HandleRequest()
{
	if (m_user->GetStatus() != LoginStatus::LoggedIn)
		throw RequestHandlerException{ "�α������� �ʾҽ��ϴ�." };

	HandleInGame();
}
