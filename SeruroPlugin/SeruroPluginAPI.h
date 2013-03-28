/**********************************************************\

  Auto-generated SeruroPluginAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "SeruroPlugin.h"

#ifndef H_SeruroPluginAPI
#define H_SeruroPluginAPI

class SeruroPluginAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn SeruroPluginAPI::SeruroPluginAPI(const SeruroPluginPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    SeruroPluginAPI(const SeruroPluginPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
        // Read-only property
        registerProperty("version",
                         make_property(this,
                                       &SeruroPluginAPI::get_version));

		// Begin SERURO additions
		registerMethod("isReady",		make_method(this, &SeruroPluginAPI::isReady));
		registerMethod("haveAddress",	make_method(this, &SeruroPluginAPI::haveAddress));
		// This is a method instead of a property to allow additional checks during
		// query-time, such as frequency and number (which may indicate a security problem).
		registerMethod("haveCert",		make_method(this, &SeruroPluginAPI::haveCert));
		registerMethod("encryptBlob",	make_method(this, &SeruroPluginAPI::encryptBlob));
		registerMethod("decryptBlob",	make_method(this, &SeruroPluginAPI::decryptBlob));

		registerMethod("apiCall",	make_method(this, &SeruroPluginAPI::apiCall));
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn SeruroPluginAPI::~SeruroPluginAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~SeruroPluginAPI() {};

    SeruroPluginPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Event helpers
    FB_JSAPI_EVENT(test, 0, ());
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));

    // Method test-event
    void testEvent();

	// Begin SERURO API calls, synchron
	FB::VariantMap isReady(FB::VariantMap);
	FB::VariantMap haveAddress(FB::VariantMap);
	FB::VariantMap haveCert(FB::VariantMap);
	FB::VariantMap encryptBlob(FB::VariantMap);
	FB::VariantMap decryptBlob(FB::VariantMap);

	// Envoke API call, async
	bool apiCall(FB::VariantMap &request, FB::JSObjectPtr &callback);

private:
	void apiHandler(FB::VariantMap& request, FB::JSObjectPtr &callback);

    SeruroPluginWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_SeruroPluginAPI

