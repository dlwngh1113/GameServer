#include "pch.h"
#include "NetworkManager.h"
#include "HandlerFactory.h"

NetworkManager NetworkManager::s_instance;

NetworkManager::NetworkManager()
{
	HandlerFactory::GetInstance().Init();
}

NetworkManager::~NetworkManager()
{
	if (m_tcpSocket != NULL)
		SDLNet_TCP_Close(m_tcpSocket);
}

bool NetworkManager::Initialize()
{
	if (SDLNet_Init() < 0)
	{
		std::cout << "SDLNet_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// SocketSet �߰�
	m_socketSet = SDLNet_AllocSocketSet(1);

	// Socket ����
	IPaddress ipAddress;
	SDLNet_ResolveHost(&ipAddress, "127.0.0.1", SERVER_PORT);
	m_tcpSocket = SDLNet_TCP_Open(&ipAddress);
	if (m_tcpSocket == NULL)
	{
		std::cerr << "������ ������ �� �����ϴ�!\n";
		return false;
	}

	// SocketSet�� �߰�
	SDLNet_TCP_AddSocket(m_socketSet, m_tcpSocket);

	return true;
}

void NetworkManager::Service()
{
	if (SDLNet_CheckSockets(m_socketSet, 0) > 0)
		ReceivePacket();
}

void NetworkManager::ReceivePacket()
{
	int nRececeiveSize = 0;
	nRececeiveSize = SDLNet_TCP_Recv(m_tcpSocket, m_pReceiveStartPtr, MAX_BUFFER);

	if (nRececeiveSize <= 0)
	{
		std::cerr << "�����κ��� ������ ������ϴ�.";
		return;
	}

	m_pNextReceivePtr = m_pReceiveStartPtr + nRececeiveSize;

	// ������� ���� �������� ��Ŷ�� ��� ��� recv
	if (nRececeiveSize < sizeof(ClientCommon::Header))
	{
		ReceiveLeftData();
		return;
	}

	// ��Ŷ�� ������ ���� ó��
	ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(m_pReceiveStartPtr);
	short snPacketType = header->type;
	short snPacketSize = header->size;

	// size��ŭ ��Ŷ�� �� ���
	while (snPacketSize <= m_pNextReceivePtr - m_pReceiveStartPtr)
	{
		ProcessPacket(m_pReceiveStartPtr, snPacketSize);

		m_pReceiveStartPtr += snPacketSize;
		if (m_pReceiveStartPtr < m_pNextReceivePtr)
		{
			header = reinterpret_cast<ClientCommon::Header*>(m_pReceiveStartPtr);
			snPacketSize = header->size;
		}
		else
			break;
	}
}

void NetworkManager::ReceiveLeftData()
{
	long long lnLeftData = m_pNextReceivePtr - m_pReceiveStartPtr;

	if ((MAX_BUFFER - (m_pNextReceivePtr - m_dataBuffer)) < MIN_BUFFER)
	{
		// ��Ŷ ó�� �� ���� �����͸� ���� ���� �������� ����
		memcpy(m_dataBuffer, m_pReceiveStartPtr, lnLeftData);
		m_pReceiveStartPtr = m_dataBuffer;
		m_pNextReceivePtr = m_pReceiveStartPtr + lnLeftData;
	}

	// �����͸� ���� ���� ����
	m_pReceiveStartPtr = m_pNextReceivePtr;
}

void NetworkManager::ProcessPacket(unsigned char* data, short snSize)
{
	ClientCommon::BasePacket* packet = reinterpret_cast<ClientCommon::BasePacket*>(data);
	
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
		std::cout << ex.what() << std::endl;
	}
}

void NetworkManager::SendPacket(unsigned char* packet, short snSize)
{
	SDLNet_TCP_Send(m_tcpSocket, packet, snSize);
}
