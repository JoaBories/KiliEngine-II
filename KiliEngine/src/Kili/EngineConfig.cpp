#include "klpch.h"
#include "EngineConfig.h"
#include "Window.h"

Kili::EngineConfig* Kili::EngineConfig::Instance = nullptr;

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
    
    mEventLogging = config.getBool("EventSystem", "logging");
}
