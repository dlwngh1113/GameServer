#include "stdafx.h"
#include "LoginRequiredRequestHandler.h"
#include "User.h"
#include "Logger.h"

void LoginRequiredRequestHandler::HandleRequest()
{
	if (m_user->GetStatus() != LoginStatus::LoggedIn)
		throw std::exception{ "로그인하지 않았습니다." };

	HandleInGame();
}
