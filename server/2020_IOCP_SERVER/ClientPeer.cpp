#include "ClientPeer.h"

ClientPeer::ClientPeer()
{
	m_recvOver.op_mode = OP_MODE_RECV;
	m_recvOver.wsa_buf.buf = reinterpret_cast<CHAR*>(m_recvOver.iocp_buf);
	m_recvOver.wsa_buf.len = sizeof(m_recvOver.iocp_buf);
	ZeroMemory(&m_recvOver, sizeof(m_recvOver));

	m_pPacketStartPos = m_recvOver.iocp_buf;
	m_pNextPacketRecvPos = m_recvOver.iocp_buf;
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

void ClientPeer::ProcessPacket()
{
	int nPacketSize = (int)m_pPacketStartPos;
	m_pNextPacketRecvPos = m_pPacketStartPos + nPacketSize;
	while (m_pPacketStartPos < m_pNextPacketRecvPos)
	{

	}
}
