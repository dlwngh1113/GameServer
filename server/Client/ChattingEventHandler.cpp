#include "pch.h"
#include "ChattingEventHandler.h"
#include "UIManager.h"
#include "Label.h"

using namespace ClientFramework;

void ChattingEventHandler::Handle()
{
	Common::ChattingResponseBody* resBody = reinterpret_cast<Common::ChattingResponseBody*>(m_packet);

	Label* chatting = (Label*)UIManager::instance().GetUI(UIType::WndChatting);
	chatting->SetText(resBody->message);
}
