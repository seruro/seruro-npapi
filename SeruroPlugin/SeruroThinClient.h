/*
 * Project: Seruro-NPAPI
 * File: SeruroThinClient.cpp
 * Description: Fire Breath project code to expose the Seruro API to a web browser.
 *
 * All project code (C)2012-2013 Valdrea, LLC. All rights reserved.
 *
 */

#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "SeruroPlugin.h"

#ifndef H_SeruroThinClient
#define H_SeruroThinClient

/*
 * @brief A client will connect as soon as it is initialized. The client should open
 *   and maintain a connection for the duration of use. This use can be defined as:
 *     1. The web browser has the extension enabled.
 *     2. The web browser is open on at least one Seruro-supported email client interface
 *     3. The web browser is performing an API call.
 *   Since the "Thick" client connection is restricted to localhost, speed and data overhead
 *   should not be considered when deciding on a connection model, over security and sense.
 */
class SeruroClient
{
public:
	SeruroClient(boost::asio::io_service& io_service,
		boost::asio::ip::tcp::endpoint localhost)
		: _service(io_service), _socket(io_service)
	{
		// callable, self handle, arguments, ...
		this->_socket.async_connect(localhost,
			boost::bind(&SeruroClient::handleConnect, this, boost::asio::placeholders::error)
		);
	}

	void write(std::string msg);
	void close();

private:
	void handleConnect(const boost::system::error_code& error);

	void handleReceive(const boost::system::error_code& error);
	void doClose();

private:
	boost::asio::io_service& _service;
	boost::asio::ip::tcp::socket _socket;

	boost::array<char, 128> _buffer;
	size_t _buffer_len;
};

void thickConnect();

#endif
