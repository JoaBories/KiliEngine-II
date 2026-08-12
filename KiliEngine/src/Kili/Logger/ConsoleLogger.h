#pragma once

#include "Log.h"

namespace Kili
{
    class ConsoleLogger : public ILogger
    {
    private:
        int mLogLevelMask;
        
    public:
        /** Don't log levels passed in mask, use the enum LogLevel. \n Example: LogLevel::Debug | LogLevel::Info */
        explicit ConsoleLogger();
        ~ConsoleLogger() override;
    
        void setLogLevelMask(const int mask) { mLogLevelMask = mask; }
        void receiveLog(const LogMessage& message) override;
    
    };
}
