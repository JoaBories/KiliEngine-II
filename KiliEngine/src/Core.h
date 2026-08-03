#pragma once

namespace Kili
{
    enum class RenderingApi : char
    {
        None,
        OpenGl,
    };

    constexpr RenderingApi RENDER_API = RenderingApi::OpenGl;
}
