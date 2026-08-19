#include "klpch.h"
#include "EngineConfig.h"

#include "../Window.h"
#include "../FileReadWrite/ConfigINI.h"
#include "../Logger/Log.h"

Kili::EngineConfig* Kili::EngineConfig::mInstance = nullptr;

Kili::EngineConfig::EngineConfig(const std::string& path)
{
    const ConfigINI config = ConfigINI::readFile(path, "KiliEngine");
    
    mWindowName = config.getString("Window", "name", "DefaultName");
    mWindowFlags = 0;
    if (config.getBool("Window", "fullscreen")) mWindowFlags |= EnumWindowFlags::WindowFullscreen;
    if (config.getBool("Window", "borderless")) mWindowFlags |= EnumWindowFlags::WindowBorderless;
    if (config.getBool("Window", "resizable")) mWindowFlags |= EnumWindowFlags::WindowResizable;
    if (config.getBool("Window", "always_on_top")) mWindowFlags |= EnumWindowFlags::WindowAlwaysOnTop;
    
    mWindowWidth = config.getInt("Window", "width", 400);
    mWindowHeight = config.getInt("Window", "height", 400);
    
    mVsync = config.getBool("Window", "vsync");
    
    mEventLogging = config.getBool("EventSystem", "logging");
    mEventLogMask = 0;
    if (!config.getBool("EventSystem", "logging_mouse_events")) mEventLogMask |= EventCategory::EventMouse;
    if (!config.getBool("EventSystem", "logging_keyboard_events")) mEventLogMask |= EventCategory::EventKeyboard;
    
    mConsoleLevelMask = 0;
    if (!config.getBool("Console", "logging_info", true)) mConsoleLevelMask |= LogLevel::Info;
    if (!config.getBool("Console", "logging_debug", true)) mConsoleLevelMask |= LogLevel::Debug;
    if (!config.getBool("Console", "logging_loading", true)) mConsoleLevelMask |= LogLevel::Loading;
    if (!config.getBool("Console", "logging_warning", true)) mConsoleLevelMask |= LogLevel::Warning;
    if (!config.getBool("Console", "logging_error", true)) mConsoleLevelMask |= LogLevel::Error;
    
    mMaxFps = config.getInt("Time", "fps_max", 60);
    mMaxDeltaTime = config.getFloat("Time", "max_delta_time", 1.0f);
    
    mFpsLogging = config.getBool("Time", "logging", false);
    mFpsLogInterval = config.getFloat("Time", "log_interval", 1.0f);
}
