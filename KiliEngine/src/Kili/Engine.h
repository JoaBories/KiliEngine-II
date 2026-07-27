#pragma once

#include "Logger/ConsoleLogger.h"

namespace Kili
{
    class Engine
    {
    private:
        ConsoleLogger* mConsoleLogger;
        bool mIsRunning;
        
        void receiveSdlLog();
        
    public:
        Engine();
        virtual ~Engine();
        
        void run();
    };
    
    // To be defined in runtime app
    Engine* createEngine();
}