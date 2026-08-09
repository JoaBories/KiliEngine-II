#pragma once

#include "Window.h"
#include "Logger/ConsoleLogger.h"

namespace Kili
{
    class Engine
    {
    private:
        ConsoleLogger* mConsoleLogger;
        Window* mWindow;
        bool mIsRunning;
        
        void receiveSdlEvents();
        
    public:
        Engine();
        virtual ~Engine();
        
        void run();
    };
    
    // To be defined in runtime app
    Engine* createEngine();
}