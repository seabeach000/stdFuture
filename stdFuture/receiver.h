#pragma once
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class receiver
{
public:
	receiver(boost::asio::io_service& io_service,
		const boost::asio::ip::address& listen_address,
		const boost::asio::ip::address& multicast_address,int multicast_port);
	virtual ~receiver();

	void handle_receive_from(const boost::system::error_code& error,
		size_t bytes_recvd);

private:
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint sender_endpoint_;
	enum 
	{
		max_length = 1500
	};
	char data_[max_length];
};

