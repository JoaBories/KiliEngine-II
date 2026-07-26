#include "klpch.h"
#include "Engine.h"

#include "Events/InputEvent.h"

namespace Kili
{
    Engine::Engine()
    {
        mConsoleLogger = new ConsoleLogger();
    }

    Engine::~Engine()
    {
        delete mConsoleLogger;
    }

    void Engine::run()
    {
        LOG_LOADING("KiliEngine Initialization");
        
        if (!SDL_Init(SDL_INIT_VIDEO)) LOG_ERROR("SDL_VIDEO could not initialize");
        else LOG_LOADING("SDL VIDEO initialized");
        
        Uint32 windowFlags = SDL_WINDOW_OPENGL;
        
        auto SdlWindow = SDL_CreateWindow("My Game", 800, 800, windowFlags);
        
        LOG_LOADING("KiliEngine Initialized");
        
        bool isRunning = true;
        
        while (isRunning)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_EVENT_QUIT:
                        isRunning = false;
                        break;
                }
            }

        }
        
        SDL_DestroyWindow(SdlWindow);
    }
}
