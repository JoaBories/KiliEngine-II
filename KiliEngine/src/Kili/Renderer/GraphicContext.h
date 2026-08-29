#pragma once

namespace Kili
{
    class IGraphicContext
    {
    public:
        virtual void init() = 0;
        virtual void close() = 0;
        virtual void swapBuffers() = 0;
    };
}