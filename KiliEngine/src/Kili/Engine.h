#pragma once

#include "Window.h"
#include "Logger/ConsoleLogger.h"

namespace Kili
{
    class Engine : public IEventListener
    {
    private:
        ConsoleLogger* mConsoleLogger;
        EventDispatcher* mEventDispatcher; // There is a EventDispatcher::instance() but i cache to avoid for less verbosity
        Window* mWindow;
        bool mIsRunning;
        
        /**
         * Init all the engine components and set them up. \n
         * Init order :
         *  - Init log and console logger. So we can see errors.
         *  - Load Engine Config from "KiliEngine.ini".
         *  - Set up log and console with their parameters.
         *  - Init and setup EventDispatcher.
         *  - Init SDL3 components (only VIDEO and GAMEPAD for now).
         *  - Create window.
         */
        void init();
        
        /**
         * Do an engine tick called while the engine is running. \n
         * Loop order :
         *  - Poll sdl events in EventDispatcher.
         */
        void loop();
        
        /**
         * Close the engine and all his components. \n
         */
        void close();
        
    protected:
        void onEvent(const IEvent& event) override { if (event.getType() == EventType::AppClose) mIsRunning = false; }
        
    public:
        Engine();
        virtual ~Engine() = default;
        
        void run(); // Called by the entry point
    };
    
    // To be defined in runtime app
    Engine* createEngine();
}