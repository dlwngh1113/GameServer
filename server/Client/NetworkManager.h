#pragma once
#include "HandlerFactory.h"
#include "Singleton.h"

class NetworkManager : public ClientFramework::Singleton<NetworkManager>
{
	TCPsocket m_socket;
	SDLNet_SocketSet m_socketSet;
	short m_packetId;

	unsigned char m_dataBuffer[MAX_BUFFER]{ NULL };
	unsigned char* m_currentBufferPos{ nullptr };

	std::chrono::seconds m_lastSendTime;
	std::unique_ptr<HandlerFactory> m_factory;
	std::unordered_map<short, std::shared_ptr<Common::Packet>> m_sendedPackets; 

public:
	NetworkManager();

private:
	void ReceiveLeftData(unsigned char* nextRecvPtr);
	void ProcessPacket(unsigned char* data, short snSize);
	void OnReceivePacket(int bytesTransferred);

	void StartConnect(boost::asio::ip::tcp::endpoint endpoint);

public:
	virtual ~NetworkManager();

	bool Initialize();
	void Service();
	void ReceivePacket();
	void SendPacket(std::shared_ptr<Common::Packet> packet);
	void SendPacket(const std::string& data);
};

