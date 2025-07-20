#include "pch.h"
#include "LoginCommandHandler.h"
#include "Scene.h"

using namespace ClientFramework;

void LoginCommandHandler::Handle()
{
	Common::LoginResponseBody resBody;
	Common::PacketStream ps(m_packet, m_packetSize);
	resBody.Deserialize(ps);

	Scene* scene = Scene::currentScene();
	if (!scene)
	{
		std::cerr << "현재 씬이 존재하지 않습니다.\n"; 
		return;
	}

	std::unique_ptr<Player> player = std::make_unique<Player>();
	player->Teleport(resBody.x, resBody.y);
	scene->SetPlayer(std::move(player));
}
