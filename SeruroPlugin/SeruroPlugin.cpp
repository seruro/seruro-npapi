/*
 * Project: Seruro-NPAPI
 * File: SeruroPlugin.cpp
 * Description: Fire Breath project code to expose the Seruro API to a web browser.
 *
 * All project code (C)2012-2013 Valdrea, LLC. All rights reserved.
 *
 */

#include "SeruroPluginAPI.h"
#include "SeruroThinClient.h"
#include "SeruroPlugin.h"

// Static SeruroPlugin variables
api_dict SeruroPlugin::seruroAPIs;
bool SeruroPlugin::thickConnected;

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
	SeruroPlugin::thickConnected = false;
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

