#pragma once

namespace Kili
{
    enum class GraphicApi : char
    {
        None,
        OpenGl,
    };

    constexpr GraphicApi GRAPHIC_API = GraphicApi::OpenGl;
    
#define BIT(offset) (1 << offset)
}
