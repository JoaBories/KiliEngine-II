#include "klpch.h"
#include "Engine.h"

#include "Events/EventDispatcher.h"
#include "Events/InputEvent.h"
#include "Events/WindowEvent.h"

namespace Kili
{
    void Engine::receiveSdlLog()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    mIsRunning = false;
                    break;
                    
                case SDL_EVENT_KEY_DOWN:
                    EventDispatcher::instance().receiveEvent(KeyInputEvent(event.key.key, true));
                    break;
                    
                case SDL_EVENT_KEY_UP:
                    EventDispatcher::instance().receiveEvent(KeyInputEvent(event.key.key, false));
                    break;
                    
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    EventDispatcher::instance().receiveEvent(MouseButtonInputEvent(event.button.button, true, Vector2{event.button.x, event.button.y}, event.button.clicks));
                    break;
                    
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    EventDispatcher::instance().receiveEvent(MouseButtonInputEvent(event.button.button, false, Vector2{event.button.x, event.button.y}, event.button.clicks));
                    break;
            }
        }
    }
    
    Engine::Engine()
    {
        mConsoleLogger = new ConsoleLogger();
        EventDispatcher::instance().setLoggingEvent(true);
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

        constexpr Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

        const auto sdlWindow = SDL_CreateWindow("My Game", 800, 800, windowFlags);
        
        LOG_LOADING("KiliEngine Initialized");
        
        mIsRunning = true;
        
        while (mIsRunning)
        {
            receiveSdlLog();
        }
        
        SDL_DestroyWindow(sdlWindow);
        
        LOG_INFO("KiliEngine Closed");
    }
}
