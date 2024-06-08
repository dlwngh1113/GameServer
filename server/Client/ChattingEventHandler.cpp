#include "pch.h"
#include "ChattingEventHandler.h"
#include "UIManager.h"
#include "Label.h"

using namespace ClientFramework;

void ChattingEventHandler::Handle()
{
	Common::ChattingResponseBody resBody;
	Common::PacketStream ps(m_packet, m_packetSize);
	resBody.Deserialize(ps);

	//Label* chatting = (Label*)UIManager::instance().GetUI(UIType::WndChatting);
	//chatting->SetText(resBody.message);

	std::cout << resBody.message << std::endl;
}
