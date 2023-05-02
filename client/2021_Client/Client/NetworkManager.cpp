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
		std::cerr << "서버에 연결할 수 없습니다!\n";
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
		std::cerr << "서버로부터 연결이 끊겼습니다.";
		return;
	}

	// 패킷의 종류에 따라 처리

	if (nRececeiveSize < sizeof(ClientCommon::Header))
	{
		// 헤더보다 작은 사이즈의 패킷일 경우 계속 recv
	}
	
	// 아닌경우 패킷 조립

}

void NetworkManager::SendPacket(unsigned char* packet, short snSize)
{
	SDLNet_TCP_Send(m_tcpSocket, packet, snSize);
}
