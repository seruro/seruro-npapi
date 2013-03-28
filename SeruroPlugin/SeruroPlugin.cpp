/**********************************************************\

  Auto-generated SeruroPlugin.cpp

  This file contains the auto-generated main plugin object
  implementation for the SeruroPlugin project

\**********************************************************/

#include "SeruroPluginAPI.h"

#include "SeruroPlugin.h"

api_dict SeruroPlugin::seruroAPIs;
bool SeruroPlugin::thickConnected;
//boost::thread SeruroPlugin::connector;

class SeruroClient
{
public:
	SeruroClient(boost::asio::io_service& io_service, 
		boost::asio::ip::tcp::resolver::iterator iterator) 
		: io_service_(io_service), socket_(io_service)
	{
		boost::asio::ip::tcp::endpoint endpoint = *iterator;
		socket_.async_connect(endpoint, boost::bind(&SeruroClient::handleConnect,
			this, boost::asio::placeholders::error, ++iterator));
	}

	void write(std::string msg)
	{
	}

	void close()
	{
		io_service_.post(boost::bind(&SeruroClient::doClose, this));
	}

private:
	void handleConnect(const boost::system::error_code& error,
		boost::asio::ip::tcp::resolver::iterator iterator)
	{
		if (!error) {
			socket_.async_receive(boost::asio::buffer(buffer_.data(), buffer_len_),
				boost::bind(&SeruroClient::handleReceive, this, boost::asio::placeholders::error)
			);
		}
		else if (iterator != boost::asio::ip::tcp::resolver::iterator())
		{
			socket_.close();
			boost::asio::ip::tcp::endpoint endpoint = *iterator;
			socket_.async_connect(endpoint,
				boost::bind(&SeruroClient::handleConnect, this,
				boost::asio::placeholders::error, ++iterator));
		}
	}

	void handleReceive(const boost::system::error_code& error)
	{
		if (error == 0) {
			//std::cout << m_Buffer.data() << std::endl;

			socket_.async_receive(boost::asio::buffer(buffer_.data(), buffer_len_),
				boost::bind(&SeruroClient::handleReceive, this, boost::asio::placeholders::error));
		} else {
			doClose();
		}
	}

	void doClose()
	{
		socket_.close();
	}

private:
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::socket socket_;

	boost::array<char, 128> buffer_;
	size_t buffer_len_;
};

void thickConnect()
{
    try {
		boost::asio::io_service io_service;

		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query("127.0.0.1", "8433");

		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

		SeruroClient client(io_service, iterator);

		boost::thread client_thread(
			boost::bind(&boost::asio::io_service::run, &io_service)
		);

		SeruroPlugin::thickConnected = true;
		//client.close();
		//client_thread.join();
    } catch (std::exception& e) {
        //std::cerr << e.what() << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @fn SeruroPlugin::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void SeruroPlugin::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process

	// Create a list of valid commands.
	SeruroPlugin::seruroAPIs["haveCert"] = true;
	SeruroPlugin::seruroAPIs["haveAddress"] = true;
	SeruroPlugin::seruroAPIs["encryptBlob"] = true;
	SeruroPlugin::seruroAPIs["decryptBlob"] = true;
	SeruroPlugin::seruroAPIs["isReady"] = true;

	// Open socket 
	boost::thread connector(thickConnect);
}

bool SeruroPlugin::validCall(std::string call)
{
	return this->seruroAPIs.count(call) > 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn SeruroPlugin::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void SeruroPlugin::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  SeruroPlugin constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
SeruroPlugin::SeruroPlugin()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  SeruroPlugin destructor.
///////////////////////////////////////////////////////////////////////////////
SeruroPlugin::~SeruroPlugin()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
    releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

void SeruroPlugin::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
}

void SeruroPlugin::shutdown()
{
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<SeruroPlugin> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr SeruroPlugin::createJSAPI()
{
    // m_host is the BrowserHost
    return boost::make_shared<SeruroPluginAPI>(FB::ptr_cast<SeruroPlugin>(shared_from_this()), m_host);
}

bool SeruroPlugin::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool SeruroPlugin::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool SeruroPlugin::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}
bool SeruroPlugin::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *)
{
    // The window is attached; act appropriately
    return false;
}

bool SeruroPlugin::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
    // The window is about to be detached; act appropriately
    return false;
}

