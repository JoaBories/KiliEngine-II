#pragma once

#include "Kili/Core/TimeClock.h"
#include "Kili/Window.h"
#include "Kili/Logger/ConsoleLogger.h"
#include "Kili/Events/Event.h"

namespace Kili
{
    class Engine
    {
    private:
        ConsoleLogger* mConsoleLogger;
        Window* mWindow;
        TimeClock* mTimeClock;
        bool mIsRunning;
        
        bool mLoggingEvents;
        int mEventLogFilter;
        
        /**
         * Init all the engine components and set them up. \n
         * Init order :
         *  - Init log and console logger. So we can see errors.
         *  - Load Engine Config from "KiliEngine.ini".
         *  - Set up log and console with their parameters.
         *  - Set up event logging.
         *  - Init SDL3 components (only VIDEO and GAMEPAD for now).
         *  - Create window.
         *  - Init and setup TimeClock.
         */
        void init();
        
        /**
         * Do an engine tick called while the engine is running. \n
         * Loop order :
         *  - Compute Time.
         *  - Poll sdl events in EventDispatcher.
         *  - Delay time if fps are locked.
         */
        void loop();
        
        /**
         * Close the engine and all his components. \n
         */
        void close();
        
        void onEvent(const IEvent& event);
        void pollEvents();
        
    public:
        Engine();
        virtual ~Engine() = default;
        
        void run(); // Called by the entry point
    };
    
    // To be defined in runtime app
    Engine* createEngine();
}