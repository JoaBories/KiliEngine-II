#include "klpch.h"
#include "Engine.h"

#include "EngineConfig.h"
#include "Events/EventDispatcher.h"
#include "Events/InputEvent.h"
#include "Events/WindowEvent.h"

namespace Kili
{
    void Engine::receiveSdlEvents()
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
                    
                case SDL_EVENT_MOUSE_MOTION:
                    EventDispatcher::instance().receiveEvent(MouseMoveInputEvent(Vector2{event.motion.x, event.motion.y}, Vector2{event.motion.xrel, event.motion.yrel}));
                    break;
                    
                case SDL_EVENT_MOUSE_WHEEL:
                    EventDispatcher::instance().receiveEvent(MouseWheelInputEvent(event.wheel.x, event.wheel.y, Vector2{event.wheel.mouse_x, event.wheel.mouse_y}, event.wheel.direction));
                    break;
                    
                case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                    EventDispatcher::instance().receiveEvent(GamepadButtonInputEvent(event.gbutton.button, true));
                    break;
                    
                case SDL_EVENT_GAMEPAD_BUTTON_UP:
                    EventDispatcher::instance().receiveEvent(GamepadButtonInputEvent(event.gbutton.button, false));
                    break;
                    
                case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                    EventDispatcher::instance().receiveEvent(GamepadAxisInputEvent(event.gaxis.axis, event.gaxis.value));
                    break;
                    
                case SDL_EVENT_WINDOW_RESIZED:
                    EventDispatcher::instance().receiveEvent(WindowResizeEvent(event.window.data1, event.window.data2));
                    break;
                    
                case SDL_EVENT_WINDOW_FOCUS_GAINED:
                    EventDispatcher::instance().receiveEvent(WindowFocusUpdateEvent(true));
                    break;
                    
                case SDL_EVENT_WINDOW_FOCUS_LOST:
                    EventDispatcher::instance().receiveEvent(WindowFocusUpdateEvent(false));
                    break;
            }
        }
    }
    
    Engine::Engine() :
        mConsoleLogger(nullptr),
        mIsRunning(false)
    {
    }

    Engine::~Engine()
    {
        delete mConsoleLogger;
    }

    void Engine::run()
    {
        Log::instance(); // Ensure a first initialization of the log
        mConsoleLogger = new ConsoleLogger();
        
        LOG_LOADING("KiliEngine Initialization");
        
        const EngineConfig* config = EngineConfig::initInstance("KiliEngine.ini");
        
        LOG_LOADING("Config loaded");
        
        EventDispatcher::instance().setLoggingEvent(config->isEventLogging());
        EventDispatcher::instance().setCategoryFilter(EventInput);
        
        if (!SDL_Init(SDL_INIT_VIDEO)) LOG_ERROR("SDL_VIDEO could not initialize");
        else LOG_LOADING("SDL VIDEO initialized");
        
        if (!SDL_Init(SDL_INIT_GAMEPAD)) LOG_ERROR("SDL GAMEPAD could not initialize");
        else LOG_LOADING("SDL GAMEPAD initialized");
        
        const WindowParameters winParams{ config->getWindowInitialWidth(), config->getWindowInitialHeight(), config->getWindowFlags(), config->isInitialVsync()};
        mWindow = new Window(config->getWindowName(), winParams);
        
        LOG_LOADING("KiliEngine Initialized");
        
        mIsRunning = true;
        
        while (mIsRunning)
        {
            receiveSdlEvents();
        }
        
        delete mWindow;
        
        LOG_INFO("KiliEngine Ended");
    }
}
