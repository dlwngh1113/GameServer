#include "stdafx.h"
#include "Peer.h"
#include "BaseRequestHandler.h"
#include "IHandlerFactory.h"
#include "Logger.h"

Peer::Peer(SOCKET socket) : m_socket{ socket }
{
	m_recvOver.op_mode = OP_MODE_RECV;
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
	unsigned char* pNextRecvPos = m_pRecvStartPos + ioSize;

	if (ioSize < sizeof(ClientCommon::Header))
	{
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
		return;
	}

	ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(m_pRecvStartPos);
	short snPacketType = header->type;
	short snPacketSize = header->size;

	// 패킷이 size만큼 도착한 경우
	while (snPacketSize <= pNextRecvPos - m_pRecvStartPos)
	{
		ProcessPacket(snPacketSize, m_pRecvStartPos);

		m_pRecvStartPos += snPacketSize;
		if (m_pRecvStartPos < pNextRecvPos)
		{
			header = reinterpret_cast<ClientCommon::Header*>(m_pRecvStartPos);
			snPacketSize = header->size;
		}
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

void Peer::Initialize(IHandlerFactory* instance)
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
		
		BaseRequestHandler* handler = m_requestHandlerFactory->CreateInstance(packet->header.type);
		handler->Initialize(shared_from_this(), packet);
		//Statics::s_threadPool.EnqueWork(std::function<void()>([&handler]() { handler->Handle(); }));
		handler->Handle();

		delete handler;
	}
	catch (std::exception& ex)
	{
		Log(ex.what());
	}
	catch (...)
	{
		Log("Default exception");
	}
}

void Peer::SendPacket(unsigned char* data, unsigned short snSize)
{
	try
	{
		//OVER EX 오브젝트 풀에서 꺼낸 후 초기화
		OVER_EX* overEx = Statics::s_overlappedPool.PopObject();
		ZeroMemory(overEx, sizeof(OVER_EX));
		overEx->op_mode = OP_MODE_SEND;
		overEx->wsa_buf.buf = reinterpret_cast<CHAR*>(overEx->iocp_buf);
		overEx->wsa_buf.len = snSize;

		//패킷 데이터 버퍼에 복사
		memcpy_s(overEx->iocp_buf, MAX_BUFFER, data, snSize);

		// Send
		m_lock.lock();
		WSASend(m_socket, &overEx->wsa_buf, 1, &overEx->wsa_buf.len, NULL, &overEx->wsa_over, NULL);
		m_lock.unlock();
	}
	catch (std::exception& ex)
	{
		Log(ex.what());
	}
	catch (...)
	{
		Log("Default exception");
	}
}

void Peer::SendPacket(ClientCommon::BasePacket* packet)
{
	unsigned char* data = reinterpret_cast<unsigned char*>(packet);
	SendPacket(data, packet->header.size);
}
