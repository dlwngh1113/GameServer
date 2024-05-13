#pragma once
#include "HandlerFactory.h"

class NetworkManager
{
	boost::asio::io_context m_context;
	boost::asio::ip::tcp::resolver m_resolver;
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::mutable_buffer m_buffer;
	short m_packetId;

	unsigned char m_dataBuffer[MAX_BUFFER]{ NULL };

	std::unique_ptr<HandlerFactory> m_factory;
	std::unordered_map<short, std::shared_ptr<Common::Packet>> m_sendedPackets; 

private:
	NetworkManager();
	void ReceiveLeftData(unsigned char* nextRecvPtr);
	void ProcessPacket(unsigned char* data, short snSize);
	void OnReceivePacket(const boost::system::error_code& error, size_t bytesTransferred);

	void StartConnect(boost::asio::ip::tcp::endpoint endpoint);

public:
	virtual ~NetworkManager();

	bool Initialize();
	void Service();
	void ReceivePacket();
	void SendPacket(std::shared_ptr<Common::Packet> packet);
	void SendPacket(char* packet, short snSize);

private:
	// Static member variables
	static NetworkManager s_instance;

public:
	// Static member functions
	static NetworkManager& instance() { return s_instance; }
};

