#include "klpch.h"
#include "Engine.h"

#include "EngineConfig.h"
#include "Events/EventDispatcher.h"

namespace Kili
{
    Engine::Engine() : IEventListener(EventCategory::EventApp),
        mConsoleLogger(nullptr),
        mEventDispatcher(nullptr),
        mWindow(nullptr),
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
        mEventDispatcher->setCategoryFilter(config->getEventLogMask());                     //
        
        if (!SDL_Init(SDL_INIT_VIDEO)) LOG_ERROR("SDL_VIDEO could not initialize");
        else LOG_LOADING("SDL VIDEO initialized");
        if (!SDL_Init(SDL_INIT_GAMEPAD)) LOG_ERROR("SDL GAMEPAD could not initialize");     // TODO make gamepad working
        else LOG_LOADING("SDL GAMEPAD initialized");
        
        const WindowParameters winParams{ config->getWindowInitialWidth(), config->getWindowInitialHeight(), config->getWindowFlags(), config->isInitialVsync()};
        mWindow = new Window(config->getWindowName(), winParams);
        
        LOG_LOADING("KiliEngine Initialized");
    }

    void Engine::loop()
    {
        mEventDispatcher->pollSdlEvents();
    }

    void Engine::close()
    {
        EngineConfig::closeInstance();
        
        delete mWindow;
        mWindow = nullptr;
        
        LOG_INFO("KiliEngine Ended");
        
        delete mConsoleLogger;
        mConsoleLogger = nullptr;
    }
}
