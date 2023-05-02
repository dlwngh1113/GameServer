#include "pch.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
	if (m_tcpSocket != NULL)
		SDLNet_TCP_Close(m_tcpSocket);
}

bool NetworkManager::Init()
{
	if (SDLNet_Init() < 0)
	{
		std::cout << "SDLNet_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	IPaddress ipAddress;
	SDLNet_ResolveHost(&ipAddress, "127.0.0.1", SERVER_PORT);
	m_tcpSocket = SDLNet_TCP_Open(&ipAddress);
	if (m_tcpSocket == NULL)
	{
		std::cerr << "������ ������ �� �����ϴ�!\n";
		return false;
	}

	return true;
}

bool NetworkManager::ConnectToServer()
{
	return true;
}

void NetworkManager::ReceivePacket()
{
	int nRececeiveSize = 0;
	nRececeiveSize = SDLNet_TCP_Recv(m_tcpSocket, m_buffer, MAX_BUFFER);

	if (nRececeiveSize <= 0)
	{
		std::cerr << "�����κ��� ������ ������ϴ�.";
		return;
	}

	// ��Ŷ�� ������ ���� ó��

	if (nRececeiveSize < sizeof(ClientCommon::Header))
	{
		// ������� ���� �������� ��Ŷ�� ��� ��� recv
	}
	
	// �ƴѰ�� ��Ŷ ����

}

void NetworkManager::SendPacket(unsigned char* packet, short snSize)
{
	SDLNet_TCP_Send(m_tcpSocket, packet, snSize);
}
