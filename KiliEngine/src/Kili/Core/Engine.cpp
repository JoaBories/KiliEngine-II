#include "klpch.h"
#include "Engine.h"

#include "EngineConfig.h"
#include "../Events/EventDispatcher.h"

namespace Kili
{
    Engine::Engine() : IEventListener(EventCategory::EventApp),
        mConsoleLogger(nullptr),
        mEventDispatcher(nullptr),
        mWindow(nullptr),
        mTimeClock(nullptr),
        mIsRunning(false)
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
        
        const EngineConfig* config = EngineConfig::initInstance("KiliEngine.ini");
        LOG_LOADING("Config loaded");
        
        mConsoleLogger->setLogLevelMask(config->getConsoleLevelMask());                     // DIST remove for build
                                                                                            //              
        mEventDispatcher = EventDispatcher::instance(); // Ensure a first initialization    //
        mEventDispatcher->setLoggingEvent(config->isEventLogging());                        //
        mEventDispatcher->setLogFilter(config->getEventLogMask());                          //
        
        if (!SDL_Init(SDL_INIT_VIDEO)) LOG_ERROR("SDL_VIDEO could not initialize");
        else LOG_LOADING("SDL VIDEO initialized");
        if (!SDL_Init(SDL_INIT_GAMEPAD)) LOG_ERROR("SDL GAMEPAD could not initialize");     // TODO make gamepad working
        else LOG_LOADING("SDL GAMEPAD initialized");
        
        const WindowParameters winParams{ config->getWindowWidth(), config->getWindowHeight(), config->getWindowFlags(), config->isVsync()};
        mWindow = new Window(config->getWindowName(), winParams);
        mWindow->init();
        
        // Temp
        SDL_GLContext context = SDL_GL_CreateContext(mWindow->getWindow());

        if (const int version = gladLoadGL(SDL_GL_GetProcAddress); !version) LOG_ERROR("OpenGL could not initialize");
        else LOG_LOADING("OpenGL " + std::to_string(GLAD_VERSION_MAJOR(version)) + "." + std::to_string(GLAD_VERSION_MINOR(version)) + " initialized");
        //
        
        mTimeClock = new TimeClock(config->getMaxFps(), config->getMaxDeltaTime());
        mTimeClock->setLogging(config->isFpsLogging());
        mTimeClock->setLoggingInterval(config->getFpsLogInterval());
        
        LOG_LOADING("KiliEngine Initialized");
    }

    void Engine::loop()
    {
        mTimeClock->computeTime();
        
        mEventDispatcher->pollSdlEvents();
        
        mTimeClock->delayTime();
    }

    void Engine::close()
    {
        EngineConfig::closeInstance();
        
        mWindow->close();
        delete mWindow;
        mWindow = nullptr;
        
        LOG_LOADING("KiliEngine Ended");
        
        delete mConsoleLogger;
        mConsoleLogger = nullptr;
    }
}
