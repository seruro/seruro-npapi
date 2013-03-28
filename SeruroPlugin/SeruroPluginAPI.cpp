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

// Read-only property version
std::string SeruroPluginAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

// Being SERURO functions
FB::VariantMap SeruroPluginAPI::isReady(FB::VariantMap params)
{
	FB::VariantMap result;
	
	result["result"] = true;
	return result;
}

FB::VariantMap SeruroPluginAPI:: haveAddress(FB::VariantMap params)
{
	FB::VariantMap result;

	result["result"] = false;
	// Must have provided an address parameter
	if (params.count("address") == 0) {
		return result;
	}

	result["result"] = true;
	return result;
}

FB::VariantMap SeruroPluginAPI::haveCert(FB::VariantMap params)
{
	FB::VariantMap result;

	result["result"] = false;
	// Must have provided an address parameter
	if (params.count("address") == 0) {
		return result;
	}

	result["result"] = true;
	return result;
}

FB::VariantMap SeruroPluginAPI::encryptBlob(FB::VariantMap params)
{
	FB::VariantMap result;

	result["result"] = false;
	// Must have an address_list, and data 
	if (params.count("address_list") == 0 || params.count("data") == 0) {
		return result;
	}

	result["data"] = "ENCRYPTED";
	result["result"] = true;
	return result;
}

FB::VariantMap SeruroPluginAPI::decryptBlob(FB::VariantMap params)
{
	FB::VariantMap result;

	result["result"] = false;
	// Must have an address, and data 
	if (params.count("address") == 0 || params.count("data") == 0) {
		return result;
	}

	result["data"] = "DECRYPTED";
	result["result"] = true;
	return result;
}

// Testing flexible API interface
void SeruroPluginAPI::apiHandler(FB::VariantMap& request, FB::JSObjectPtr &callback)
{
	FB::VariantMap result;
	FB::VariantMap params;
	std::string call;

	call = request["api"].convert_cast<std::string>();
	params = request["params"].convert_cast<FB::VariantMap>();

	// Check each command
	if (call.compare("haveCert") == 0) {
		result = this->haveCert(params);
	} else if (call.compare("haveAddress") == 0) {
		result = this->haveAddress(params);
	} else if (call.compare("encryptBlob") == 0) {
		result = this->encryptBlob(params);
	} else if (call.compare("decryptBlob") == 0) {
		result = this->decryptBlob(params);
	} else if (call.compare("isReady") == 0) {
		result = this->isReady(params);
	}

	// If no function is provided, this will crash the plugin
	callback->InvokeAsync("", FB::variant_list_of(result));
}

// Should be the only method exposed
bool SeruroPluginAPI::apiCall(FB::VariantMap &request, FB::JSObjectPtr &callback)
{
	// Check to make sure this call is "valid"
	if (request.count("api") == 0 ||
		! this->getPlugin()->validCall(request["api"].convert_cast<std::string>())) 
		return false;
	// Create an apiHandler thread, to continue evaluation async
	boost::thread api_thread(
		boost::bind(&SeruroPluginAPI::apiHandler, this, request, callback)
	);
	return true;
}