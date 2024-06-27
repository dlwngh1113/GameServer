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

	void BaseCommandHandler::Initialize(std::shared_ptr<Peer> peer, unsigned char* data, size_t size)
	{
		m_peer = peer;
		m_data.resize(size);
		memcpy_s(m_data.data(), m_data.size(), data, size);
	}

	void BaseCommandHandler::SendResponse(std::shared_ptr<Common::ResponseBody> response)
	{
		Common::PacketStream ps;
		response->code = kCode_Success;
		std::string data = response->Serialize(ps);

		m_peer->SendData(data);
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