#include "stdafx.h"
#include "receiver.h"
#include <iostream>
receiver::receiver(boost::asio::io_service& io_service, const boost::asio::ip::address& listen_address, 
	const boost::asio::ip::address& multicast_address, int multicast_port)
	:socket_(io_service)
{
	// Create the socket so that multiple may be bound to the same address.  
	boost::asio::ip::udp::endpoint listen_endpoint(
		listen_address, multicast_port);
	socket_.open(listen_endpoint.protocol());
	socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
	socket_.bind(listen_endpoint);

	// Join the multicast group.  
	socket_.set_option(
		boost::asio::ip::multicast::join_group(multicast_address));

	socket_.async_receive_from(
		boost::asio::buffer(data_, max_length), sender_endpoint_,
		boost::bind(&receiver::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

receiver::~receiver()
{
}

void receiver::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
	if (!error)
	{
		std::cout.write(data_, bytes_recvd);
		std::cout << std::endl;

		socket_.async_receive_from(
			boost::asio::buffer(data_, max_length), sender_endpoint_,
			boost::bind(&receiver::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
}
