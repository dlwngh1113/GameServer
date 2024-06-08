#include "pch.h"
#include "ChattingEventHandler.h"
#include "UIManager.h"
#include "Label.h"
#include "Scene.h"

using namespace ClientFramework;

void ChattingEventHandler::Handle()
{
	Common::ChattingResponseBody resBody;
	Common::PacketStream ps(m_packet, m_packetSize);
	resBody.Deserialize(ps);

	Scene* currentScene(Scene::currentScene());
	if (currentScene)
	{
		Label* label(currentScene->GetLabel());
		label->SetText(resBody.message);
	}
	
	std::cout << resBody.message << std::endl;
}
