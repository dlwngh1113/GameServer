#pragma once

class NetworkManager
{
	static NetworkManager s_instance;
	TCPsocket m_tcpSocket{ NULL };

	unsigned char m_dataBuffer[MAX_BUFFER]{ NULL };
	unsigned char m_packetBuffer[MAX_BUFFER]{ NULL };
	unsigned char* m_pReceiveStartPtr{ m_dataBuffer };
	unsigned char* m_pNextReceivePtr{ m_dataBuffer };

private:
	NetworkManager();
	void ReceiveLeftData();
	void ProcessPacket(unsigned char* data, short snSize);

public:
	virtual ~NetworkManager();
	NetworkManager(const NetworkManager& other) = delete;
	NetworkManager& operator=(const NetworkManager& other) = delete;

	bool Initialize();
	void LoginToServer(const char* sName);
	void ReceivePacket();
	void SendPacket(ClientCommon::BasePacket* packet);
	void SendPacket(unsigned char* packet, short snSize);

	static NetworkManager& GetInstance()
	{
		return s_instance;
	}
};

