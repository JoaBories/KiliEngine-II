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
    
    mWindowInitialWidth = config.getInt("Window", "width", 400);
    mWindowInitialHeight = config.getInt("Window", "height", 400);
    
    mInitialFpsLimit = config.getInt("Window", "fps_limit", 60);
    mInitialVsync = config.getBool("Window", "vsync");
    
    mEventLogging = config.getBool("Logging", "logging_events");
    mEventLogMask = 0;
    if (!config.getBool("Logging", "logging_mouse_events")) mEventLogMask |= EventCategory::EventMouse;
    if (!config.getBool("Logging", "logging_keyboard_events")) mEventLogMask |= EventCategory::EventKeyboard;
    
    mConsoleLevelMask = 0;
    if (!config.getBool("Console", "logging_info", true)) mConsoleLevelMask |= LogLevel::Info;
    if (!config.getBool("Console", "logging_debug", true)) mConsoleLevelMask |= LogLevel::Debug;
    if (!config.getBool("Console", "logging_loading", true)) mConsoleLevelMask |= LogLevel::Loading;
    if (!config.getBool("Console", "logging_warning", true)) mConsoleLevelMask |= LogLevel::Warning;
    if (!config.getBool("Console", "logging_error", true)) mConsoleLevelMask |= LogLevel::Error;
}
