#pragma once

#include "klpch.h"

namespace Kili
{
    struct WindowParameters
    {
        int msaa;
        bool vsync;
        bool fullscreen;
        bool borderless;
        bool alwaysOnTop;
        bool resizable;
    };
    
    class Window
    {
    private:
        SDL_Window* mWindow;
        std::string mTitle;
        unsigned int mWidth, mHeight;
        bool mVsync;
    
        void init();
        void close();
        
    public:
        Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        
        void onUpdate();
        
        [[nodiscard]] unsigned int getWidth() const { return mWidth; }
        [[nodiscard]] unsigned int getHeight() const { return mHeight; }
        
        [[nodiscard]] SDL_Window* getWindow() const { return mWindow; }
        
        [[nodiscard]] bool isVsync() const { return mVsync; }
        
        void setVsync(bool vsync);
        
    };
}
