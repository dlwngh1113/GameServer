#pragma once

namespace JCore
{
	class Peer
	{
	private:
		boost::asio::ip::tcp::socket m_socket;
		boost::uuids::uuid m_id;

	public:
		Peer(boost::asio::io_context& context);

		const boost::asio::ip::tcp::socket& socket() const;
		boost::asio::ip::tcp::socket& socket();

		// Static Member Functions
	public:
		static shared_ptr<Peer> Create(boost::asio::io_context& context);
	};
}