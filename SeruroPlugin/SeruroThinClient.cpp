/*
 * Project: Seruro-NPAPI
 * File: SeruroThinClient.cpp
 * Description: Fire Breath project code to expose the Seruro API to a web browser.
 *
 * All project code (C)2012-2013 Valdrea, LLC. All rights reserved.
 *
 */

#include <boost/thread.hpp>

#include "SeruroThinClient.h"

//using boost::asio::ip;

/*
 * The "Thin<->Thick" connection will only talk ASCII strings over a local connection.
 */
void SeruroClient::write(std::string msg) {}

void SeruroClient::close()
{
	this->_service.post(boost::bind(&SeruroClient::doClose, this));
}


void SeruroClient::handleConnect(const boost::system::error_code& error)
{
	if (error) {
		// Do something to log error and display to interface
		return;
	}

	this->_socket.async_receive(boost::asio::buffer(this->_buffer.data(), this->_buffer_len),
		boost::bind(&SeruroClient::handleReceive, this, boost::asio::placeholders::error)
	);
}

void SeruroClient::handleReceive(const boost::system::error_code& error)
{
	if (error) {
		// Do something to log error and display to interface
		this->doClose();
		return;
	}

	//std::cout << m_Buffer.data() << std::endl;
	//this->socket_.async_receive(boost::asio::buffer(this->_buffer.data(), this->_buffer_len),
	//	boost::bind(&SeruroClient::handleReceive, this, boost::asio::placeholders::error));
}

void SeruroClient::doClose()
{
	this->_socket.close();
}

/* Start a connection to the Seruro "Thick" client. */
void thickConnect()
{
    try {
		boost::asio::io_service io_service;
		// boost::asio::tcp::endpoint
		boost::asio::ip::tcp::endpoint localhost(
			boost::asio::ip::address::from_string("127.0.0.1"), 8433
		);

		SeruroClient client(io_service, localhost);

		boost::thread client_thread(
			boost::bind(&boost::asio::io_service::run, &io_service)
		);

		SeruroPlugin::thickConnected = true;
		//client.close();
		//client_thread.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
