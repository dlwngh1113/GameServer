#include "stdafx.h"
#include "ClientPeer.h"
#include "BaseRequestHandlerFactory.h"
#include "BaseRequestHandler.h"
#include "BaseApplication.h"

namespace Core
{
	ClientPeer::ClientPeer(Peer* peer, BaseRequestHandlerFactory* instance)
		: m_peer{ peer }
	{
		m_factory = instance;
		m_peer->ProcessPacket = [this](char* data, size_t size) { this->ProcessPacket(data, size); };
	}

	ClientPeer::~ClientPeer()
	{
	}

	void ClientPeer::ProcessPacket(char* data, size_t size)
	{
		ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(data);
		try
		{
			if (m_factory == nullptr)
				throw std::exception{ "RequestHandlerFactory is nullptr!" /* + m_peer->id()*/ };

			std::shared_ptr<BaseRequestHandler> handler = m_factory->Create(header->type);
			handler->Initialize(this, header);

			// add to thread work
			
			boost::asio::post(BaseApplication::threads(), [handler]() {handler->Handle(); });
			//Global::GetInstance().threadPool.EnqueWork([handler]() { handler->Handle(); });
		}
		catch (std::exception& ex)
		{
			std::cout << "[Error] - " << ex.what() << std::endl;
		}
	}

	void ClientPeer::SendPacket(char* data, size_t size)
	{
		m_peer->SendData(data, size);
	}
}