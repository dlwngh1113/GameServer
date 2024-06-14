#include "pch.h"
#include "NetworkManager.h"
#include "Framework.h"
#include "BaseHandler.h"
#include "Time.h"

NetworkManager NetworkManager::s_instance;

NetworkManager::NetworkManager()
	: m_socket(nullptr)
	, m_currentBufferPos(m_dataBuffer)
	, m_lastSendTime(std::chrono::seconds::min())
	, m_factory(std::make_unique<HandlerFactory>())
	, m_packetId(0)
{
}

NetworkManager::~NetworkManager()
{
	m_thread.join();
}

bool NetworkManager::Initialize()
{
	IPaddress serverIp;
	SDLNet_ResolveHost(&serverIp, "127.0.0.1", SERVER_PORT);

	m_socketSet = SDLNet_AllocSocketSet(1);

	m_socket = SDLNet_TCP_Open(&serverIp);
	if (m_socket)
	{
		SDLNet_TCP_AddSocket(m_socketSet, m_socket);
		m_thread = std::thread{ &NetworkManager::ReceivePacket, this };
	}
	
	//
	// Initialize Handler Factory
	//

	m_factory->Initialize();

	return m_socket != nullptr;
}

void NetworkManager::Service()
{
	std::shared_ptr<BaseHandler> handler(nullptr);
	if (m_handlers.try_pop(handler))
		handler->Handle();
}

void NetworkManager::ReceivePacket()
{
	while (true)
	{
		if (SDLNet_CheckSockets(m_socketSet, 0) > 0)
		{
			try
			{
				int bytesTransferred = SDLNet_TCP_Recv(m_socket, m_currentBufferPos, MAX_BUFFER);
				if (bytesTransferred > 0)
					OnReceivePacket(bytesTransferred);
				else
				{
					std::cerr << "서버로부터 연결이 끊겼습니다.";
					return;
				}
			}
			catch (std::exception& ex)
			{
				std::cerr << ex.what() << std::endl;
			}
		}
	}
}

void NetworkManager::OnReceivePacket(int bytesTransferred)
{
	unsigned char* pNextRecvPos = m_currentBufferPos + bytesTransferred;

	if (bytesTransferred < sizeof(Common::Header))
	{
		ReceiveLeftData(pNextRecvPos);
		return;
	}

	Common::Header* header = reinterpret_cast<Common::Header*>(m_currentBufferPos);
	short snPacketType = header->type;
	short snPacketSize = header->size;

	// 패킷이 size만큼 도착한 경우
	while (snPacketSize <= pNextRecvPos - m_currentBufferPos)
	{
		ProcessPacket(m_currentBufferPos, snPacketSize);

		m_currentBufferPos += snPacketSize;
		if (m_currentBufferPos < pNextRecvPos)
		{
			header = reinterpret_cast<Common::Header*>(m_currentBufferPos);
			snPacketSize = header->size;
		}
		else
			break;
	}

	ReceiveLeftData(pNextRecvPos);
}

void NetworkManager::ReceiveLeftData(unsigned char* nextRecvPtr)
{
	long long lnLeftData = nextRecvPtr - m_currentBufferPos;

	if ((MAX_BUFFER - (nextRecvPtr - m_currentBufferPos)) < MIN_BUFFER)
	{
		// 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
		memcpy(m_dataBuffer, m_currentBufferPos, lnLeftData);
		nextRecvPtr = m_dataBuffer + lnLeftData;
	}

	m_currentBufferPos = nextRecvPtr;
}

void NetworkManager::ProcessPacket(unsigned char* data, short snSize)
{
	Common::Header* header = reinterpret_cast<Common::Header*>(data);
	
	Event cmd = static_cast<Event>(header->type);
	try
	{
		std::shared_ptr<BaseHandler> handler = m_factory->Create(cmd);
		handler->Initialize(data, snSize);
		m_handlers.push(handler);
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}

void NetworkManager::SendPacket(std::shared_ptr<Common::Packet> packet)
{
	// Increase packet id
	packet->id = ++m_packetId;

	// Serialize packet
	Common::PacketStream ps;
	std::string data = packet->Serialize(ps);

	//m_sendedPackets.insert(std::make_pair(packet->id + 1, packet));
	SendPacket(data);
}

void NetworkManager::SendPacket(const std::string& data)
{
	std::chrono::seconds now(std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()).time_since_epoch());
	if (m_lastSendTime.count() + 1 > now.count())
		return;

	try
	{
		SDLNet_TCP_Send(m_socket, data.data(), data.size());
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	m_lastSendTime = now;
}
