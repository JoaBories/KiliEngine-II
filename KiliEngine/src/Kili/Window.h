#pragma once

#include "klpch.h"

#include "Events/EventDispatcher.h"

namespace Kili
{
    enum EnumWindowFlags : char
    {
        None = 0,
        WindowFullscreen =  1 << 0,
        WindowBorderless =  1 << 1,
        WindowAlwaysOnTop = 1 << 2,
        WindowResizable =   1 << 3,
    };
    
    struct WindowParameters
    {
        /** Height and Width in pixel if not fullscreen. **/
        unsigned int height, width;
        /** Flags from EnumWindowFlags. \n Example : WindowVsync | WindowFullscreen | WindowBorderless. **/
        char flags;
        /** The window should start with vsync or no **/
        bool vsync; 
    };
    
    class Window : public IEventListener
    {
    private:
        std::string mTitle;
        SDL_Window* mWindow;
        unsigned int mWidth, mHeight;
        char mFlags;
        bool mVsync;
    
        void init();
        void close();
        
    public:
        Window(std::string title, WindowParameters params);
        virtual ~Window();
        
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;
        
        [[nodiscard]] SDL_Window* getWindow() const { return mWindow; }
        
        [[nodiscard]] unsigned int getWidth() const { return mWidth; }
        [[nodiscard]] unsigned int getHeight() const { return mHeight; }
        
        [[nodiscard]] char getFlags() const { return mFlags; }
        
        [[nodiscard]] bool isVsync() const { return mVsync; }
        void setVsync(bool vsync);

    protected:
        void onEvent(const Event& event) override;
    };
}
