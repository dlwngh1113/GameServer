#pragma once

namespace Core
{
	class Peer : enable_shared_from_this<Peer>
	{
	private:
		boost::asio::streambuf m_buffer;
		boost::asio::ip::tcp::socket m_socket;
		boost::uuids::uuid m_id;

	public:
		Peer(boost::asio::io_context& context);

		const boost::uuids::uuid& id() const;
		boost::asio::ip::tcp::socket& socket();

		void ReceivePacket();
		void SendPacket(unsigned char* data, size_t size);

	protected:
		virtual void OnReceivedData(const boost::system::error_code& error, size_t size);

		// Static Member Functions
	public:
		static shared_ptr<Peer> Create(boost::asio::io_context& context);
	};
}