#include "stdafx.h"
#include "BaseRequestHandler.h"
#include "Peer.h"

namespace Core
{
	BaseRequestHandler::BaseRequestHandler()
		: m_header{ nullptr }
		, m_peer{ nullptr }
	{
	}

	BaseRequestHandler::~BaseRequestHandler()
	{
	}

	void BaseRequestHandler::Initialize(ClientPeer* peer, ClientCommon::Header* header)
	{
		m_peer = peer;
		m_header = header;
	}
}