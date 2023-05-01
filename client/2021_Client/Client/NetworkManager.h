#pragma once

class NetworkManager
{
	TCPsocket m_tcpSocket{ NULL };

	unsigned char m_buffer[MAX_BUFFER];
	unsigned char* m_pCurrentReceivePtr{ nullptr };

public:
	NetworkManager();
	virtual ~NetworkManager();

	bool Init();
	bool ConnectToServer();
	void ReceivePacket();
	void SendPacket(unsigned char* packet, short snSize);
};

