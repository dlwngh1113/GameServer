#pragma once
#include "Uuid.h"

namespace Core
{
	class BaseApplication;

	class Peer : enable_shared_from_this<Peer>
	{
	private:
		boost::asio::ip::tcp::socket m_socket;

		boost::array<char, MAX_BUFFER> m_processBuffer;
		size_t m_bufferOffset;
		boost::asio::streambuf m_buffer;

		boost::uuids::uuid m_id;
		BaseApplication* m_application;

	public:
		explicit Peer(boost::asio::ip::tcp::socket&& socket, BaseApplication* application) noexcept;

		const boost::uuids::uuid& id() const;
		boost::asio::ip::tcp::socket& socket();

		void ReceiveData();
		void SendData(unsigned char* data, size_t size);

	protected:
		virtual void OnReceiveData(const boost::system::error_code& error, size_t bytesTransferred);
		
	private:
		void ReceiveLeftData(char* pNextRecvPos);
		void Disconnect();

		// Static Member Functions
	public:
		static shared_ptr<Peer> Create(boost::asio::ip::tcp::socket&& socket, BaseApplication* application);
	};
}