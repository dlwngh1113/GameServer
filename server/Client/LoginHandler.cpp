#include "pch.h"
#include "LoginHandler.h"
#include "Framework.h"
#include "Scene.h"
#include "MyPlayer.h"

LoginHandler::LoginHandler()
{
}

LoginHandler::~LoginHandler()
{
}

void LoginHandler::Handle()
{
	ClientCommon::LoginResponse* packet = reinterpret_cast<ClientCommon::LoginResponse*>(m_packet);

	MyPlayer* myPlayer = MyPlayer::Create(packet->id);
	myPlayer->SetPosition(packet->x, packet->y, 64, 64);

	Scene* scene = new Scene;
	scene->SetPlayer(myPlayer);

	Framework::GetInstance().ChangeScene(scene);
}

Handler* LoginHandler::Create()
{
	return new LoginHandler;
}
