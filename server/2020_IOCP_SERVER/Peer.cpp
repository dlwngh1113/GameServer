#include"stdafx.h"
#include"Peer.h"
#include"BaseRequestHandler.h"
#include"IHandlerFactory.h"

Peer::Peer(SOCKET socket) : m_socket{ socket }
{
	m_recvOver.op_mode = ClientCommon::OP_MODE_RECV;
	m_recvOver.wsa_buf.buf = reinterpret_cast<CHAR*>(m_recvOver.iocp_buf);
	m_recvOver.wsa_buf.len = sizeof(m_recvOver.iocp_buf);
	ZeroMemory(&m_recvOver.wsa_over, sizeof(m_recvOver.wsa_over));

	m_pRecvStartPos = m_recvOver.iocp_buf;
	StartRecv();
}

void Peer::StartRecv()
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
			Log("WSA Error - " + err_no);
	}
}

Peer::~Peer()
{
	closesocket(m_socket);
}

void Peer::ProcessIO(DWORD ioSize)
{
	int nPacketSize = (int)m_pRecvStartPos[0];
	unsigned char* pNextRecvPos = m_pRecvStartPos + ioSize;

	// 패킷이 size만큼 도착한 경우
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

	if ((ClientCommon::MAX_BUFFER - (pNextRecvPos - m_recvOver.iocp_buf)) < ClientCommon::MIN_BUFFER)
	{
		// 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
		memcpy(m_recvOver.iocp_buf, m_pRecvStartPos, lnLeftData);
		m_pRecvStartPos = m_recvOver.iocp_buf;
		pNextRecvPos = m_pRecvStartPos + lnLeftData;
	}

	// 데이터를 받을 버퍼 세팅
	m_pRecvStartPos = pNextRecvPos;
	m_recvOver.wsa_buf.buf = reinterpret_cast<CHAR*>(pNextRecvPos);
	m_recvOver.wsa_buf.len = ClientCommon::MAX_BUFFER - static_cast<int>(pNextRecvPos - m_recvOver.iocp_buf);

	StartRecv();
}

void Peer::Init(IHandlerFactory* instance)
{
	m_requestHandlerFactory = instance;
}

void Peer::ProcessPacket(unsigned char size, unsigned char* data)
{
	ClientCommon::BasePacket* packet = reinterpret_cast<ClientCommon::BasePacket*>(data);
	try
	{
		if (m_requestHandlerFactory == nullptr)
			throw std::exception{ "RequestHandlerFactory is nullptr!" + m_socket };
		
		BaseRequestHandler* handler = m_requestHandlerFactory->CreateInstance(packet->type);
		handler->Init(this, packet);
		handler->Handle();

		delete handler;
	}
	catch (std::exception& ex)
	{
		Log(ex.what());
	}
}

void Peer::SendPacket(unsigned char* data)
{
	try
	{
		//OVER EX 오브젝트 풀에서 꺼낸 후 초기화
		OVER_EX* overEx = Statics::overlappedPool.PopObject();
		ZeroMemory(overEx, sizeof(OVER_EX));
		overEx->op_mode = ClientCommon::OP_MODE_SEND;
		overEx->wsa_buf.buf = reinterpret_cast<CHAR*>(overEx->iocp_buf);
		overEx->wsa_buf.len = data[0];

		//패킷 데이터 버퍼에 복사
		memcpy_s(overEx->iocp_buf, ClientCommon::MAX_BUFFER, data, data[0]);

		// Send
		m_lock.lock();
		WSASend(m_socket, &overEx->wsa_buf, 1, &overEx->wsa_buf.len, NULL, &overEx->wsa_over, NULL);
		m_lock.unlock();
	}
	catch (std::exception& ex)
	{
		Log(ex.what());
	}
}

void Peer::SendPacket(ClientCommon::BasePacket* packet)
{
	unsigned char* data = reinterpret_cast<unsigned char*>(packet);
	SendPacket(data);
}
