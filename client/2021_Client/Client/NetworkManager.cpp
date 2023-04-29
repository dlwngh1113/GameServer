#include "pch.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
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
