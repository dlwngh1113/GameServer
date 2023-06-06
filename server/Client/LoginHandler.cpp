#include "pch.h"
#include "LoginHandler.h"
#include "Framework.h"
#include "Scene.h"

LoginHandler::LoginHandler()
{
}

LoginHandler::~LoginHandler()
{
}

void LoginHandler::Handle()
{
	ClientCommon::LoginResponse* packet = reinterpret_cast<ClientCommon::LoginResponse*>(m_packet);
	Framework::GetInstance().ChangeScene(new Scene);
}

Handler* LoginHandler::Create()
{
	return new LoginHandler;
}
