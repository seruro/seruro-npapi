/**********************************************************\

  Auto-generated SeruroPluginAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "SeruroPluginAPI.h"

#include "boost/thread.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant SeruroPluginAPI::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript.
///         Go ahead and change it. See what happens!
///////////////////////////////////////////////////////////////////////////////
FB::variant SeruroPluginAPI::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo("So far, you clicked this many times: ", n++);

    // return "foobar";
    return msg;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn SeruroPluginPtr SeruroPluginAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
SeruroPluginPtr SeruroPluginAPI::getPlugin()
{
    SeruroPluginPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read/Write property testString
std::string SeruroPluginAPI::get_testString()
{
    return m_testString;
}

void SeruroPluginAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string SeruroPluginAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void SeruroPluginAPI::testEvent()
{
    fire_test();
}

// Being SERURO functions
bool SeruroPluginAPI::isReady()
{
	return true;
}

FB::variant SeruroPluginAPI:: myAddresses()
{
	FB::variant addr_list("teddy.reed@gmail.com");
	return addr_list;
}

bool SeruroPluginAPI::haveCert(const FB::variant& address)
{
	return true;
}

std::string SeruroPluginAPI::encryptBlob(const FB::variant& address_list, const FB::variant& blob)
{
	std::string enc_blob("ENCRYPTED");
	return enc_blob;
}

std::string SeruroPluginAPI::decryptBlob(const FB::variant& address, const FB::variant& blob)
{
	std::string dec_blob("DECRYPTED");
	return dec_blob;
}

// Testing flexible API interface
void SeruroPluginAPI::haveCertAPI(FB::VariantMap& request, FB::JSObjectPtr &callback)
{
	FB::variant result(true);
	callback->InvokeAsync("", FB::variant_list_of(result));
}

bool SeruroPluginAPI::apiCall(FB::VariantMap &request, FB::JSObjectPtr &callback)
{
	if (request["api"].convert_cast<std::string>().compare("haveCert") == 0) {
		boost::thread api_thread(
			boost::bind(
				&SeruroPluginAPI::haveCertAPI, 
				this, request, callback)
		);
	}
	return true;
}