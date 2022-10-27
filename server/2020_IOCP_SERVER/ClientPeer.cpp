#include "ClientPeer.h"

ClientPeer::ClientPeer()
{
	m_recvOver.op_mode = OP_MODE_RECV;
	m_recvOver.wsa_buf.buf = reinterpret_cast<CHAR*>(m_recvOver.iocp_buf);
	m_recvOver.wsa_buf.len = sizeof(m_recvOver.iocp_buf);
	ZeroMemory(&m_recvOver, sizeof(m_recvOver));

	m_pRecvStartPos = m_recvOver.iocp_buf;
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
	StartRecv();
}

void ClientPeer::StartRecv()
{
	DWORD flags = 0;
	int ret;
	m_lock.lock();
	ret = WSARecv(m_socket, &m_recvOver.wsa_buf, 1, NULL, &flags, &m_recvOver.wsa_over, NULL);
	m_lock.unlock();
	if (SOCKET_ERROR == ret) 
	{
		int err_no = WSAGetLastError();
		if (ERROR_IO_PENDING != err_no)
			Logger::Error("WSA Error - " + err_no);
	}
}

void ClientPeer::ProcessIO(DWORD ioSize)
{
	int nPacketSize = (int)m_pRecvStartPos[0];
	unsigned char* pNextRecvPos = m_pRecvStartPos + ioSize;

	while (nPacketSize <= pNextRecvPos - m_pRecvStartPos)
	{
		ProcessPacket(nPacketSize, m_pRecvStartPos);

		m_pRecvStartPos += nPacketSize;
		if (m_pRecvStartPos < pNextRecvPos)
			nPacketSize = m_pRecvStartPos[0];
		else
			break;
	}

	long long lnLeftData = pNextRecvPos - m_pRecvStartPos;

	if ((MAX_BUFFER - (pNextRecvPos - m_recvOver.iocp_buf)) < MIN_BUFFER)
	{
		// 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
		memcpy(m_recvOver.iocp_buf, m_pRecvStartPos, lnLeftData);
		m_pRecvStartPos = m_recvOver.iocp_buf;
		pNextRecvPos = m_pRecvStartPos + lnLeftData;
	}

	// 데이터를 받을 버퍼 세팅
	m_pRecvStartPos = pNextRecvPos;
	m_recvOver.wsa_buf.buf = reinterpret_cast<CHAR*>(pNextRecvPos);
	m_recvOver.wsa_buf.len = MAX_BUFFER - static_cast<int>(pNextRecvPos - m_recvOver.iocp_buf);

	StartRecv();
}

void ClientPeer::ProcessPacket(BasePacket* packet)
{
}

void ClientPeer::ProcessPacket(unsigned char size, unsigned char* data)
{
	BasePacket* packet = reinterpret_cast<BasePacket*>(data);
	ProcessPacket(packet);
}