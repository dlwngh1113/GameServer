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
		return;

	std::unique_ptr<Player> player = std::make_unique<Player>();
	player->Teleport(resBody.x, resBody.y);
	scene->AddObject(std::move(player));
}
