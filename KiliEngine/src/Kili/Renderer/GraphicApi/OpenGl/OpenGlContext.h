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
        explicit OpenGlContext(SDL_Window* windowHandle);
        virtual ~OpenGlContext() = default;
        
        void init() override;
        void swapBuffers() override;
        void close() override;
    };
}
