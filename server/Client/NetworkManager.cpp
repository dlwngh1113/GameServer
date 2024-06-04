#include "pch.h"
#include "NetworkManager.h"
#include "Framework.h"
#include "BaseHandler.h"
#include "Time.h"

NetworkManager NetworkManager::s_instance;

NetworkManager::NetworkManager()
	: m_socket(m_context)
	, m_buffer(m_dataBuffer, MAX_BUFFER)
	, m_lastSendTime(std::chrono::seconds::min())
	, m_factory(std::make_unique<HandlerFactory>())
	, m_packetId(0)
{
}

NetworkManager::~NetworkManager()
{
	m_socket.close();
}

bool NetworkManager::Initialize()
{
	StartConnect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address_v4("127.0.0.1"), SERVER_PORT));

	return true;
}

void NetworkManager::StartConnect(boost::asio::ip::tcp::endpoint endpoint)
{
	m_socket.async_connect(endpoint, [this](const boost::system::error_code& error) {
		std::cout << "Executed connecting\n";
		if (!error)
		{
			std::cout << "StartConnect finished\n";
			Service();
		}
		});
}

void NetworkManager::Service()
{
	std::cout << "context is running\n";
	ReceivePacket();
	m_context.run();
}

void NetworkManager::ReceivePacket()
{
	try
	{
		m_socket.async_receive(boost::asio::buffer(m_buffer),
			bind(&NetworkManager::OnReceivePacket, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void NetworkManager::OnReceivePacket(const boost::system::error_code& error, size_t bytesTransferred)
{
	if (bytesTransferred <= 0)
	{
		std::cerr << "서버로부터 연결이 끊겼습니다.";
		return;
	}

	unsigned char* currentBufferPos = reinterpret_cast<unsigned char*>(m_buffer.data());
	unsigned char* pNextRecvPos = currentBufferPos + bytesTransferred;

	if (bytesTransferred < sizeof(Common::Header))
	{
		ReceiveLeftData(pNextRecvPos);
		return;
	}

	Common::Header* header = reinterpret_cast<Common::Header*>(currentBufferPos);
	short snPacketType = header->type;
	short snPacketSize = header->size;

	// 패킷이 size만큼 도착한 경우
	while (snPacketSize <= pNextRecvPos - currentBufferPos)
	{
		ProcessPacket(currentBufferPos, snPacketSize);

		currentBufferPos += snPacketSize;
		if (currentBufferPos < pNextRecvPos)
		{
			header = reinterpret_cast<Common::Header*>(currentBufferPos);
			snPacketSize = header->size;
		}
		else
			break;
	}

	ReceiveLeftData(pNextRecvPos);
}

void NetworkManager::ReceiveLeftData(unsigned char* nextRecvPtr)
{
	unsigned char* currentReceivePos = reinterpret_cast<unsigned char*>(m_buffer.data());
	long long lnLeftData = nextRecvPtr - currentReceivePos;

	if ((MAX_BUFFER - (nextRecvPtr - currentReceivePos)) < MIN_BUFFER)
	{
		// 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
		memcpy(m_dataBuffer, currentReceivePos, lnLeftData);
		m_buffer = boost::asio::mutable_buffer(m_dataBuffer, MAX_BUFFER);
		nextRecvPtr = m_dataBuffer + lnLeftData;
	}

	m_buffer = boost::asio::mutable_buffer(nextRecvPtr, MAX_BUFFER - lnLeftData);

	ReceivePacket();
}

void NetworkManager::ProcessPacket(unsigned char* data, short snSize)
{
	Common::Header* header = reinterpret_cast<Common::Header*>(data);
	
	Event cmd = static_cast<Event>(header->type);
	try
	{
		std::shared_ptr<BaseHandler> handler = m_factory->Create(cmd);
		handler->Initialize(data, snSize);
		handler->Handle();
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

	m_sendedPackets.insert(std::make_pair(packet->id + 1, packet));
	SendPacket(data);
}

void NetworkManager::SendPacket(const std::string& data)
{
	std::chrono::seconds now(std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()).time_since_epoch());
	if (m_lastSendTime.count() + 1 > now.count())
		return;

	try
	{
		m_socket.async_send(boost::asio::buffer(data), [](const boost::system::error_code& error, size_t bytesTransferred) {});
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	m_lastSendTime = now;
}
