#include "klpch.h"
#include "Engine.h"

#include "Kili/Core/EngineConfig.h"

#include "Kili/Events/InputEvent.h"
#include "Kili/Events/WindowEvent.h"
#include "Kili/FileReadWrite/ConfigINI.h"

namespace Kili
{
    void Engine::pollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_EVENT_QUIT:
                onEvent(WindowCloseEvent());
                break;
                
            case SDL_EVENT_KEY_DOWN:
                onEvent(KeyEvent(event.key.key, true, event.key.repeat));
                break;
                
            case SDL_EVENT_KEY_UP:
                onEvent(KeyEvent(event.key.key, false, event.key.repeat));
                break;
                
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                onEvent(MouseButtonEvent(
                    event.button.button, true, 
                    Vector2{event.button.x, event.button.y}, 
                    event.button.clicks));
                break;
                
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onEvent(MouseButtonEvent(
                    event.button.button, false, 
                    Vector2{event.button.x, event.button.y}, 
                    event.button.clicks));
                break;
                
            case SDL_EVENT_MOUSE_MOTION:
                onEvent(MouseMoveEvent(
                    Vector2{event.motion.x, event.motion.y}, 
                    Vector2{event.motion.xrel, event.motion.yrel}));
                break;
                
            case SDL_EVENT_MOUSE_WHEEL:
                onEvent(MouseWheelEvent(
                    event.wheel.x, 
                    event.wheel.y, 
                    Vector2{event.wheel.mouse_x, event.wheel.mouse_y}, 
                    event.wheel.direction));
                break;
                
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                onEvent(GamepadButtonEvent(event.gbutton.button, true));
                break;
                
            case SDL_EVENT_GAMEPAD_BUTTON_UP:
                onEvent(GamepadButtonEvent(event.gbutton.button, false));
                break;
                
            case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                onEvent(GamepadAxisEvent(event.gaxis.axis, event.gaxis.value));
                break;
                
            case SDL_EVENT_WINDOW_RESIZED:
                onEvent(WindowResizeEvent(event.window.data1, event.window.data2));
                break;
                
            case SDL_EVENT_WINDOW_FOCUS_GAINED:
                onEvent(WindowFocusUpdateEvent(true));
                break;
                
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                onEvent(WindowFocusUpdateEvent(false));
                break;
            }
        }
    }
    
    void Engine::onEvent(const IEvent& event)
    {
        // Catch close event
        DispatchEvent<WindowCloseEvent>(event, [this](const WindowCloseEvent& e) { mIsRunning = false; });
        
        //Future possible usages of events :
        //mInputManager->onEvent(event);
        //mWindow->onEvent(event);
        
        if (mLoggingEvents)
        {
            if (event.hasCategories(mEventLogFilter)) return;
            LOG_DEBUG(event.toString());
        }
    }
    
    Engine::Engine() : 
        mConsoleLogger(nullptr),
        mWindow(nullptr),
        mTimeClock(nullptr),
        mIsRunning(false),
        mLoggingEvents(true), mEventLogFilter(EventMouse)
    {
    }

    void Engine::run()
    {
        init();
        
        mIsRunning = true;
        
        while (mIsRunning)
        {
            loop();
        }
        
        close();
    }

    void Engine::init()
    {
        Log::instance(); // Ensure a first initialization of the log
        mConsoleLogger = new ConsoleLogger();
        
        LOG_LOADING("KiliEngine Initialization");
        
        const EngineConfig config("KiliEngine.ini", "KiliEngine");
        LOG_LOADING("Config loaded");
        
        mConsoleLogger->setLogLevelMask(config.getConsoleLevelMask());
        
        mLoggingEvents = config.isEventLogging();
        mEventLogFilter = config.getEventLogFilter();
        
        if (!SDL_Init(SDL_INIT_VIDEO)) LOG_ERROR("SDL_VIDEO could not initialize");
        else LOG_LOADING("SDL VIDEO initialized");
        if (!SDL_Init(SDL_INIT_GAMEPAD)) LOG_ERROR("SDL GAMEPAD could not initialize");     // TODO make gamepad working
        else LOG_LOADING("SDL GAMEPAD initialized");
        
        const WindowParameters winParams{ config.getWindowWidth(), config.getWindowHeight(), config.getWindowFlags(), config.isVsync()};
        mWindow = new Window(config.getWindowName(), winParams);
        mWindow->init();
        
        // Temp
        SDL_GLContext context = SDL_GL_CreateContext(mWindow->getWindow());

        if (const int version = gladLoadGL(SDL_GL_GetProcAddress); !version) LOG_ERROR("OpenGL could not initialize");
        else LOG_LOADING("OpenGL " + std::to_string(GLAD_VERSION_MAJOR(version)) + "." + std::to_string(GLAD_VERSION_MINOR(version)) + " initialized");
        //
        
        mTimeClock = new TimeClock(config.getMaxFps(), config.getMaxDeltaTime());
        mTimeClock->setLogging(config.isFpsLogging());
        mTimeClock->setLoggingInterval(config.getFpsLogInterval());
        
        LOG_LOADING("KiliEngine Initialized");
    }

    void Engine::loop()
    {
        mTimeClock->computeTime();
        
        pollEvents();
        
        mTimeClock->delayTime();
    }

    void Engine::close()
    {
        mWindow->close();
        delete mWindow;
        mWindow = nullptr;
        
        LOG_LOADING("KiliEngine Ended");
        
        delete mConsoleLogger;
        mConsoleLogger = nullptr;
    }
}
