#include "stdafx.h"
#include "BaseCommandHandler.h"

namespace Core
{
	BaseCommandHandler::BaseCommandHandler()
		: m_peer{ nullptr }
	{
	}

	BaseCommandHandler::~BaseCommandHandler()
	{
	}

	void BaseCommandHandler::Initialize(Peer* peer, const uint8_t* data, size_t size)
	{
		m_peer = peer;
		m_data.resize(size);
		memcpy(m_data.data(), data, size);
	}

	void BaseCommandHandler::SendResponse(Common::ResponseBody* response)
	{
		response->code = kCode_Success;
		m_peer->SendData(response);
	}

	void BaseCommandHandler::Error(short code, const std::string& message)
	{
		//Common::PacketStream ps;
		//std::shared_ptr<Common::ResponseBody> res = std::make_shared<Common::ResponseBody>();
		//res->code = code;
		//res->message = message;

		//std::string data = res->Serialize(ps);

		//m_peer->SendData(data);
	}
}