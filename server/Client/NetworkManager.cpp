#include "pch.h"
#include "NetworkManager.h"
#include "Framework.h"
#include "BaseHandler.h"
#include "Time.h"

NetworkManager::NetworkManager()
	: m_socket(nullptr)
	, m_socketSet(SDLNet_AllocSocketSet(1))
	, m_lastSendTime(std::chrono::seconds::min())
	, m_factory(std::make_unique<HandlerFactory>())
	, m_packetId(0)
	, m_buffer(MAX_BUFFER)
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
				int bytesTransferred = SDLNet_TCP_Recv(m_socket, m_buffer.GetWriteBuffer(), m_buffer.GetWriteBufferSize());
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
	auto leftBytes = bytesTransferred;
	m_buffer.AddReceivedSize(leftBytes);

	if (leftBytes < sizeof(Common::Header))
	{
		return;
	}

	static thread_local uint8_t pBuffer[MAX_BUFFER]{};
	m_buffer.Peek(pBuffer, leftBytes);

	Common::Header header{};
	do
	{
		m_buffer.Peek(reinterpret_cast<uint8_t*>(&header), sizeof(header));

		ProcessPacket(header.type, header.size);

		leftBytes -= header.size;
		m_buffer.Pop(pBuffer, header.size);
	} while (m_buffer.GetReadableSize() > 0);
}

void NetworkManager::ProcessPacket(int16_t type, int16_t size)
{
	Event cmd = static_cast<Event>(type);
	try
	{
		std::shared_ptr<BaseHandler> handler = m_factory->Create(cmd);
		handler->Initialize(m_buffer.GetReadBuffer(), size);
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
		SDLNet_TCP_Send(m_socket, data.data(), (int)data.size());
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	m_lastSendTime = now;
}
