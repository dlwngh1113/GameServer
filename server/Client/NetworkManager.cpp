#include "pch.h"
#include "NetworkManager.h"
#include "HandlerFactory.h"
#include "Framework.h"

NetworkManager NetworkManager::s_instance;

NetworkManager::NetworkManager()
	: m_socket(m_context)
	, m_resolver(m_context)
{
	HandlerFactory::GetInstance().Init();
}

NetworkManager::~NetworkManager()
{
	m_socket.close();
}

bool NetworkManager::Initialize()
{
	//m_resolver.async_resolve(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address_v4("127.0.0.1"), SERVER_PORT),
	//	[](const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator it) {
	//		if (!error) {
	//			boost::asio::ip::tcp::endpoint endpoint = *it;
	//			NetworkManager::GetInstance().StartConnect(endpoint);
	//		}
	//		else {
	//			std::cerr << "Error resolving address: " << error.message() << std::endl;
	//		}
	//	});

	m_socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address_v4("127.0.0.1"), SERVER_PORT));

	return true;
}

void NetworkManager::StartConnect(boost::asio::ip::tcp::endpoint endpoint)
{
	m_socket.async_connect(endpoint, [](const boost::system::error_code& error) {});
}

void NetworkManager::Service()
{
	ReceivePacket();
}

void NetworkManager::ReceivePacket()
{
	m_socket.async_receive(boost::asio::buffer(m_dataBuffer),
		bind(&NetworkManager::OnReceivePacket, this, placeholders::_1, placeholders::_2));
}

void NetworkManager::OnReceivePacket(const boost::system::error_code& error, size_t bytesTransferred)
{
	if (bytesTransferred <= 0)
	{
		std::cerr << "�����κ��� ������ ������ϴ�.";
		return;
	}

	// ������� ���� �������� ��Ŷ�� ��� ��� recv
	if (bytesTransferred < sizeof(ClientCommon::Header))
	{
		ReceiveLeftData();
		return;
	}

	//// ��Ŷ�� ������ ���� ó��
	//ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(m_pReceiveStartPtr);
	//short snPacketType = header->type;
	//short snPacketSize = header->size;

	//// size��ŭ ��Ŷ�� �� ���
	//while (snPacketSize <= m_pNextReceivePtr - m_pReceiveStartPtr)
	//{
	//	ProcessPacket(m_pReceiveStartPtr, snPacketSize);

	//	m_pReceiveStartPtr += snPacketSize;
	//	if (m_pReceiveStartPtr < m_pNextReceivePtr)
	//	{
	//		header = reinterpret_cast<ClientCommon::Header*>(m_pReceiveStartPtr);
	//		snPacketSize = header->size;
	//	}
	//	else
	//		break;
	//}
}

void NetworkManager::ReceiveLeftData()
{
	//long long lnLeftData = m_pNextReceivePtr - m_pReceiveStartPtr;

	//if ((MAX_BUFFER - (m_pNextReceivePtr - m_dataBuffer)) < MIN_BUFFER)
	//{
	//	// ��Ŷ ó�� �� ���� �����͸� ���� ���� �������� ����
	//	memcpy(m_dataBuffer, m_pReceiveStartPtr, lnLeftData);
	//	m_pReceiveStartPtr = m_dataBuffer;
	//	m_pNextReceivePtr = m_pReceiveStartPtr + lnLeftData;
	//}

	//// �����͸� ���� ���� ����
	//m_pReceiveStartPtr = m_pNextReceivePtr;
}

void NetworkManager::ProcessPacket(unsigned char* data, short snSize)
{
	ClientCommon::Packet* packet = reinterpret_cast<ClientCommon::Packet*>(data);
	
	ServerEvent cmd = static_cast<ServerEvent>(packet->header.type);
	try
	{
		Handler* handler = HandlerFactory::GetInstance().GetHandler(cmd);
		handler->Init(data, snSize);
		handler->Handle();
		delete handler;
	}
	catch (std::exception& ex)
	{
		Framework::GetInstance().ShowError(ex.what());
	}
}

void NetworkManager::SendPacket(unsigned char* packet, short snSize)
{
	m_socket.async_send(boost::asio::buffer(packet, snSize), [](const boost::system::error_code& error, size_t bytesTransferred) {});
}
