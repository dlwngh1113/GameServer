#include "stdafx.h"
#include "LoginRequiredRequestHandler.h"
#include "User.h"

void LoginRequiredRequestHandler::HandleRequest()
{
	if (m_user->GetStatus() != LoginStatus::LogedIn)
		throw std::exception{ "로그인하지 않았습니다." };

	HandleInGame();
}
