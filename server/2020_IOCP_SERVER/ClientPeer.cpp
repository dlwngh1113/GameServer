#include "ClientPeer.h"

ClientPeer::ClientPeer()
{

}

ClientPeer::~ClientPeer()
{
}

void ClientPeer::OnDisconnect()
{
}

void ClientPeer::Init(SOCKET ns)
{
	m_socket = ns;
}
