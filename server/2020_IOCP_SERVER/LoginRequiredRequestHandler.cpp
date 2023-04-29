#include "stdafx.h"
#include "LoginRequiredRequestHandler.h"
#include "User.h"

void LoginRequiredRequestHandler::HandleRequest()
{
	if (m_user->GetStatus() != LoginStatus::LoggedIn)
		throw std::exception{ "�α������� �ʾҽ��ϴ�." };

	HandleInGame();
}
