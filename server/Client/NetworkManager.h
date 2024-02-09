#pragma once

class NetworkManager
{
	static NetworkManager s_instance;
	boost::asio::io_context m_context;
	boost::asio::ip::tcp::socket m_socket;

	char m_dataBuffer[MAX_BUFFER]{ NULL };

private:
	NetworkManager();
	void ReceiveLeftData();
	void ProcessPacket(unsigned char* data, short snSize);
	void OnReceivePacket(const boost::system::error_code& error, size_t bytesTransferred);

public:
	virtual ~NetworkManager();
	NetworkManager(const NetworkManager& other) = delete;
	NetworkManager& operator=(const NetworkManager& other) = delete;

	bool Initialize();
	void Service();
	void ReceivePacket();
	void SendPacket(unsigned char* packet, short snSize);

	static NetworkManager& GetInstance()
	{
		return s_instance;
	}
};

