#include "klpch.h"
#include "Window.h"
#include "Events/WindowEvent.h"
#include "Logger/Log.h"

void Kili::Window::init()
{
    int windowFlags = 0;
    
    if constexpr (RENDER_API == RenderingApi::None)
    {
        LOG_WARNING("Rendering Api None isn't supported");
    }
    else if constexpr (RENDER_API == RenderingApi::OpenGl)
    {
        SDL_GL_SetSwapInterval(mVsync);
        windowFlags |= SDL_WINDOW_OPENGL;
    }
    
    // ADDAPI
    
    if (mFlags & WindowFullscreen) windowFlags |= SDL_WINDOW_FULLSCREEN;
    if (mFlags & WindowBorderless) windowFlags |= SDL_WINDOW_BORDERLESS;
    if (mFlags & WindowResizable) windowFlags |= SDL_WINDOW_RESIZABLE;
    if (mFlags & WindowAlwaysOnTop) windowFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
    
    mWindow = SDL_CreateWindow(mTitle.c_str(), static_cast<int>(mWidth), static_cast<int>(mHeight), windowFlags);
}

void Kili::Window::close()
{
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
}

Kili::Window::Window(std::string title, const WindowParameters params) :
    IEventListener(EventWindow),
    mTitle(std::move(title)), mWindow(nullptr), 
    mWidth(params.width), mHeight(params.height), 
    mFlags(params.flags), mVsync(params.vsync)
{
}

void Kili::Window::setVsync(const bool vsync)
{
    mVsync = vsync;
    
    if constexpr (RENDER_API == RenderingApi::None)
    {
        LOG_WARNING("Rendering Api None does not support Vsync");
    }
    else if constexpr (RENDER_API == RenderingApi::OpenGl)
    {
        SDL_GL_SetSwapInterval(mVsync);
    }
    
    // ADDAPI
}

void Kili::Window::onEvent(const IEvent& event)
{
    if (event.getType() == EventType::WindowResize)
    {
        const auto& resizeEvent = static_cast<const WindowResizeEvent&>(event);
        mHeight = resizeEvent.getHeight();
        mWidth = resizeEvent.getWidth();
        // Todo implement proper window resize
    }
}
