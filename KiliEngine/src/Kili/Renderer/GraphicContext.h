#pragma once

#include "SDL.h"

namespace Kili
{
    class IGraphicContext
    {
    public:
        virtual ~IGraphicContext() = default;
        
        virtual void init(SDL_Window* windowHandle) = 0;
        virtual void close() = 0;
        virtual void swapBuffers() = 0;
        
        virtual int getWindowFlag() const = 0;
        
        virtual void setVsync(bool enabled) = 0;
        virtual bool getVsync() const = 0;
        
        virtual void setMsaa(int samples) = 0;
    };
}