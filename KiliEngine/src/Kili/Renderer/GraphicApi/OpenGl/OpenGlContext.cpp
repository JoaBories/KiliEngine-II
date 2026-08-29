#include "klpch.h"
#include "OpenGlContext.h"

#include "Kili/Logger/Log.h"

Kili::OpenGlContext::OpenGlContext(SDL_Window* windowHandle) :
    mWindowHandle(windowHandle)
{
    
}

void Kili::OpenGlContext::init()
{
    mContext = SDL_GL_CreateContext(mWindowHandle);
    if (const int version = gladLoadGL(SDL_GL_GetProcAddress); !version) LOG_ERROR("OpenGL could not initialize");
    else LOG_LOADING("OpenGL " + std::to_string(GLAD_VERSION_MAJOR(version)) + "." + std::to_string(GLAD_VERSION_MINOR(version)) + " initialized");
}

void Kili::OpenGlContext::swapBuffers()
{
    SDL_GL_SwapWindow(mWindowHandle);
}

void Kili::OpenGlContext::close()
{
    SDL_GL_DestroyContext(mContext);
}