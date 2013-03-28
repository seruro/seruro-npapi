/**********************************************************\

  Auto-generated SeruroPlugin.h

  This file contains the auto-generated main plugin object
  implementation for the SeruroPlugin project

\**********************************************************/
#ifndef H_SeruroPluginPLUGIN
#define H_SeruroPluginPLUGIN

#include "PluginWindow.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"

#include "PluginCore.h"

#include <string>
#include <vector>
#include <map>

#include "boost/thread.hpp"
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>

// Could be a map of API_NAME->ARG_LIST
typedef std::map<std::string, bool > api_dict;

FB_FORWARD_PTR(SeruroPlugin)
class SeruroPlugin : public FB::PluginCore
{
public:
	// The initializer should populate the valid API calls.
    static void StaticInitialize();
    static void StaticDeinitialize();
	// We can call this from the plugin API to check if the command
	// is valid.
	bool validCall(std::string call);
	// Make local connection to thick client listener.
	//void thickConnect();
	static bool thickConnected;

private:
	static api_dict seruroAPIs;
	//static boost::thread connector;


public:
    SeruroPlugin();
    virtual ~SeruroPlugin();

public:
    void onPluginReady();
    void shutdown();
    virtual FB::JSAPIPtr createJSAPI();
    // If you want your plugin to always be windowless, set this to true
    // If you want your plugin to be optionally windowless based on the
    // value of the "windowless" param tag, remove this method or return
    // FB::PluginCore::isWindowless()
    virtual bool isWindowless() { return true; }

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::MouseDownEvent, onMouseDown, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseUpEvent, onMouseUp, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindow)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindow)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *);
    virtual bool onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *);
    virtual bool onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *);
    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/
};


#endif

