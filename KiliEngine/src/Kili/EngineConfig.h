#pragma once
#include "FileReadWrite/ConfigINI.h"

namespace Kili
{
    class EngineConfig
    {
        friend class Engine; // So only Engine can access Instance creation and deletion
        
        static EngineConfig* Instance;
    
        // Window parameters
        std::string mWindowName;
        char mWindowFlags;
        unsigned int mWindowInitialWidth;
        unsigned int mWindowInitialHeight;
        int mInitialFpsLimit;
        bool mInitialVsync;
    
        // Event system
        bool mEventLogging;
        
        explicit EngineConfig(const std::string& path);
        ~EngineConfig() = default;
        
        static EngineConfig* initInstance(const std::string& configPath) { Instance = new EngineConfig(configPath); return Instance; }
        static void closeInstance() { delete Instance; Instance = nullptr; }
        
    public:
        /** If it returns nullptr wait until engine initialize the instance */
        static EngineConfig* getInstance() { return Instance; }
        
        [[nodiscard]] std::string getWindowName() const { return mWindowName; }
        [[nodiscard]] char getWindowFlags() const { return mWindowFlags; }
        [[nodiscard]] unsigned int getWindowInitialWidth() const { return mWindowInitialWidth; }
        [[nodiscard]] unsigned int getWindowInitialHeight() const { return mWindowInitialHeight; }
        [[nodiscard]] int getInitialFpsLimit() const { return mInitialFpsLimit; }
        [[nodiscard]] bool isInitialVsync() const { return mInitialVsync; }
        
        [[nodiscard]] bool isEventLogging() const { return mEventLogging; }
    };
}
