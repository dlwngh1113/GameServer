#pragma once
#include "HandlerFactory.h"

class NetworkManager
{
	boost::asio::io_context m_context;
	boost::asio::ip::tcp::resolver m_resolver;
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::mutable_buffer m_buffer;

	unsigned char m_dataBuffer[MAX_BUFFER]{ NULL };

	std::unique_ptr<HandlerFactory> m_factory;

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
	void SendPacket(unsigned char* packet, short snSize);

private:
	// Static member variables
	static NetworkManager s_instance;

public:
	// Static member functions
	static NetworkManager& GetInstance()
	{
		return s_instance;
	}
};

