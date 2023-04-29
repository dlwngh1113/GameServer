#pragma once

class NetworkManager
{
	TCPsocket m_tcpSocket{ NULL };
public:
	NetworkManager();
	virtual ~NetworkManager();

	bool Init();
};

