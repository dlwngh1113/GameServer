﻿#include "stdafx.h"
#include "Peer.h"
#include "BaseRequestHandler.h"
#include "BaseRequestHandlerFactory.h"
#include "Logger.h"
#include "CServer.h"

Peer::Peer(SOCKET socket) : m_socket{ socket }
{
	m_recvOver.op_mode = OP_MODE_RECV;
	m_recvOver.wsa_buf.buf = reinterpret_cast<CHAR*>(m_recvOver.iocp_buf);
	m_recvOver.wsa_buf.len = sizeof(m_recvOver.iocp_buf);
	ZeroMemory(&m_recvOver.wsa_over, sizeof(m_recvOver.wsa_over));

	m_pReceiveStartPtr = m_recvOver.iocp_buf;
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

void Peer::Initialize(BaseRequestHandlerFactory* instance)
{
	m_requestHandlerFactory = instance;
}

Peer::~Peer()
{
	closesocket(m_socket);
}

void Peer::ProcessIO(DWORD ioSize)
{
	unsigned char* pNextRecvPos = m_pReceiveStartPtr + ioSize;

	if (ioSize < sizeof(ClientCommon::Header))
	{
		ReceiveLeftData(pNextRecvPos);
		return;
	}

	ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(m_pReceiveStartPtr);
	short snPacketType = header->type;
	short snPacketSize = header->size;

	// 패킷이 size만큼 도착한 경우
	while (snPacketSize <= pNextRecvPos - m_pReceiveStartPtr)
	{
		ProcessPacket(m_pReceiveStartPtr, snPacketSize);

		m_pReceiveStartPtr += snPacketSize;
		if (m_pReceiveStartPtr < pNextRecvPos)
		{
			header = reinterpret_cast<ClientCommon::Header*>(m_pReceiveStartPtr);
			snPacketSize = header->size;
		}
		else
			break;
	}

	ReceiveLeftData(pNextRecvPos);
}

void Peer::ReceiveLeftData(unsigned char* pNextRecvPos)
{
	long long lnLeftData = pNextRecvPos - m_pReceiveStartPtr;

	if ((MAX_BUFFER - (pNextRecvPos - m_recvOver.iocp_buf)) < MIN_BUFFER)
	{
		// 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
		memcpy(m_recvOver.iocp_buf, m_pReceiveStartPtr, lnLeftData);
		m_pReceiveStartPtr = m_recvOver.iocp_buf;
		pNextRecvPos = m_pReceiveStartPtr + lnLeftData;
	}

	// 데이터를 받을 버퍼 세팅
	m_pReceiveStartPtr = pNextRecvPos;
	m_recvOver.wsa_buf.buf = reinterpret_cast<CHAR*>(pNextRecvPos);
	m_recvOver.wsa_buf.len = MAX_BUFFER - static_cast<int>(pNextRecvPos - m_recvOver.iocp_buf);

	StartRecv();
}

void Peer::ProcessPacket(unsigned char* data, unsigned short snSize)
{
	ClientCommon::BasePacket* packet = reinterpret_cast<ClientCommon::BasePacket*>(data);
	try
	{
		if (m_requestHandlerFactory == nullptr)
			throw std::exception{ "RequestHandlerFactory is nullptr!" + m_socket };
		
		std::shared_ptr<BaseRequestHandler> handler = m_requestHandlerFactory->Create(packet->header.type);
		handler->Initialize(this, packet);

		Global::GetInstance().threadPool.EnqueWork([handler]() { handler->Handle(); });
	}
	catch (std::exception& ex)
	{
		Log(ex.what());
	}
}

void Peer::SendPacket(unsigned char* data, unsigned short snSize)
{
	try
	{
		//OVER EX 오브젝트 풀에서 꺼낸 후 초기화
		OVER_EX* overEx = Global::GetInstance().overlappedPool.PopObject();
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
}

void Peer::SendPacket(ClientCommon::BasePacket* packet)
{
	unsigned char* data = reinterpret_cast<unsigned char*>(packet);
	SendPacket(data, packet->header.size);
}
