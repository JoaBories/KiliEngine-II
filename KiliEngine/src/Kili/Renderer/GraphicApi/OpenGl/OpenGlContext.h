#pragma once
#include "Kili/Renderer/GraphicContext.h"

namespace Kili
{
    class OpenGlContext : public IGraphicContext
    {
    private:
        SDL_Window* mWindowHandle;
        SDL_GLContext mContext;
        
    public:
        OpenGlContext() = default;
        
        void init(SDL_Window* windowHandle) override;
        void close() override;
        
        void swapBuffers() override { SDL_GL_SwapWindow(mWindowHandle); }
        
        [[nodiscard]] int getWindowFlag() const override { return SDL_WINDOW_OPENGL; }
        
        void setMsaa(int samples) override;
        
        void setVsync(const bool enabled) override { SDL_GL_SetSwapInterval(enabled); }
        [[nodiscard]] bool getVsync() const override { int interval; SDL_GL_GetSwapInterval(&interval); return interval;  }
    };
}
