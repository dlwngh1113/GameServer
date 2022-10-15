#include "ClientPeer.h"

ClientPeer::ClientPeer()
{

}

ClientPeer::~ClientPeer()
{
}

void ClientPeer::Init(SOCKET ns)
{
	m_socket = ns;
}
