#include "pch.h"
#include "Peer.h"
#include "Header.h"

namespace JCore
{
	Peer::Peer(SOCKET socket) : m_socket{ socket }
	{
		m_recvOver.opMode = OP_RECV;
		m_recvOver.wsaBuf.buf = reinterpret_cast<CHAR*>(m_recvOver.iocpBuf);
		m_recvOver.wsaBuf.len = sizeof(m_recvOver.iocpBuf);
		ZeroMemory(&m_recvOver.wsaOver, sizeof(m_recvOver.wsaOver));

		m_pReceiveStartPtr = m_recvOver.iocpBuf;
		StartRecv();
	}

	void Peer::StartRecv()
	{
		DWORD flags = 0;
		int ret;
		ret = WSARecv(m_socket, &m_recvOver.wsaBuf, 1, NULL, &flags, &m_recvOver.wsaOver, NULL);
		if (SOCKET_ERROR == ret)
		{
			int errorNum = WSAGetLastError();
			if (ERROR_IO_PENDING != errorNum)
				std::cout << "[Error " << errorNum << "]\n";
		}
	}

	Peer::~Peer()
	{
		closesocket(m_socket);
	}

	void Peer::ProcessIO(DWORD ioSize)
	{
		unsigned char* pNextRecvPos = m_pReceiveStartPtr + ioSize;

		if (ioSize < sizeof(Header))
		{
			ReceiveLeftData(pNextRecvPos);
			return;
		}

		Header* header = reinterpret_cast<Header*>(m_pReceiveStartPtr);
		short snPacketType = header->type;
		short snPacketSize = header->size;

		// 패킷이 size만큼 도착한 경우
		while (snPacketSize <= pNextRecvPos - m_pReceiveStartPtr)
		{
			OnProcessPacket(m_pReceiveStartPtr, snPacketSize);

			m_pReceiveStartPtr += snPacketSize;
			if (m_pReceiveStartPtr < pNextRecvPos)
			{
				header = reinterpret_cast<Header*>(m_pReceiveStartPtr);
				snPacketSize = header->size;
			}
			else
				break;
		}

		ReceiveLeftData(pNextRecvPos);
	}

	void Peer::OnProcessPacket(unsigned char* data, unsigned short snSize)
	{
	}

	void Peer::ReceiveLeftData(unsigned char* pNextRecvPos)
	{
		long long lnLeftData = pNextRecvPos - m_pReceiveStartPtr;

		if ((MAX_BUFFER - (pNextRecvPos - m_recvOver.iocpBuf)) < MIN_BUFFER)
		{
			// 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
			memcpy(m_recvOver.iocpBuf, m_pReceiveStartPtr, lnLeftData);
			m_pReceiveStartPtr = m_recvOver.iocpBuf;
			pNextRecvPos = m_pReceiveStartPtr + lnLeftData;
		}

		// 데이터를 받을 버퍼 세팅
		m_pReceiveStartPtr = pNextRecvPos;
		m_recvOver.wsaBuf.buf = reinterpret_cast<CHAR*>(pNextRecvPos);
		m_recvOver.wsaBuf.len = MAX_BUFFER - static_cast<int>(pNextRecvPos - m_recvOver.iocpBuf);

		StartRecv();
	}

	void Peer::SendPacket(unsigned char* data, unsigned short snSize)
	{
		try
		{
			//OVER EX 오브젝트 풀에서 꺼낸 후 초기화
			//OverlappedExtension* overEx = Global::GetInstance().overlappedPool.PopObject();
			OverlappedExtension* overEx = new OverlappedExtension();
			ZeroMemory(overEx, sizeof(OverlappedExtension));
			overEx->opMode = OP_SEND;
			overEx->wsaBuf.buf = reinterpret_cast<CHAR*>(overEx->iocpBuf);
			overEx->wsaBuf.len = snSize;

			//패킷 데이터 버퍼에 복사
			memcpy_s(overEx->iocpBuf, MAX_BUFFER, data, snSize);

			// Send
			m_lock.lock();
			WSASend(m_socket, &overEx->wsaBuf, 1, &overEx->wsaBuf.len, NULL, &overEx->wsaOver, NULL);
			m_lock.unlock();
		}
		catch (std::exception& ex)
		{
			std::cout << "[Error] - " << ex.what() << std::endl;
		}
	}
}