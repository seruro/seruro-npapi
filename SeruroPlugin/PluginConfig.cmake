#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for SeruroPlugin
#
#\**********************************************************/

set(PLUGIN_NAME "SeruroPlugin")
set(PLUGIN_PREFIX "SPL")
set(COMPANY_NAME "VLABS")

# ActiveX constants:
set(FBTYPELIB_NAME SeruroPluginLib)
set(FBTYPELIB_DESC "SeruroPlugin 1.0 Type Library")
set(IFBControl_DESC "SeruroPlugin Control Interface")
set(FBControl_DESC "SeruroPlugin Control Class")
set(IFBComJavascriptObject_DESC "SeruroPlugin IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "SeruroPlugin ComJavascriptObject Class")
set(IFBComEventSource_DESC "SeruroPlugin IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID ddd6e3c6-e7dd-549f-9441-0c45b0a32db5)
set(IFBControl_GUID 6bf53348-e4bd-54b9-9ad6-703c492e9d79)
set(FBControl_GUID a4917264-9e40-5c82-83cf-e3be86cf8e88)
set(IFBComJavascriptObject_GUID c5cb136e-c7ce-5413-b8b8-601e395889c2)
set(FBComJavascriptObject_GUID c06cc38d-91d9-5d2c-bd7a-241ba90cbf23)
set(IFBComEventSource_GUID 3b5376e0-93b9-560a-aa33-69498db75fb6)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 68097cf3-7c7e-5f84-89fe-b9defeaa8542)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 26e866bb-eee5-55be-95dc-1c3543e30672)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "VLABS.SeruroPlugin")
set(MOZILLA_PLUGINID "valdrea.com/SeruroPlugin")

# strings
set(FBSTRING_CompanyName "Valdrea, LLC")
set(FBSTRING_PluginDescription "A Seruro thin client which implements the simple Seruro API.")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2013 Valdrea, LLC")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "SeruroPlugin")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "SeruroPlugin")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "SeruroPlugin_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-seruroplugin")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
