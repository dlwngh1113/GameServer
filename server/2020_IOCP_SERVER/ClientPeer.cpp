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

	DWORD flags = 0;
	int ret;
	m_lock.lock();
	ret = WSARecv(m_socket, &m_recvOver.wsa_buf, 1, NULL, &flags, &m_recvOver.wsa_over, NULL);
	m_lock.unlock();
	if (SOCKET_ERROR == ret) {
		int err_no = WSAGetLastError();
		if (ERROR_IO_PENDING != err_no)
			Logger::Error("WSA Error - " + err_no);
	}
}
