#pragma once

class NetworkManager
{
	TCPsocket m_tcpSocket{ NULL };

	unsigned char m_dataBuffer[MAX_BUFFER]{ NULL };
	unsigned char m_packetBuffer[MAX_BUFFER]{ NULL };
	unsigned char* m_pReceiveStartPtr{ m_dataBuffer };
	unsigned char* m_pNextReceivePtr{ m_dataBuffer };

private:
	void ReceiveLeftData();
	void ProcessPacket(unsigned char* data, short snSize);

public:
	NetworkManager();
	virtual ~NetworkManager();

	bool Initialize();
	void LoginToServer(const char* sName);
	void ReceivePacket();
	void SendPacket(ClientCommon::BasePacket* packet);
	void SendPacket(unsigned char* packet, short snSize);
};

