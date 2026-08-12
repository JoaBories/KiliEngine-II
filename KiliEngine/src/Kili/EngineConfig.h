#pragma once

namespace Kili
{
    class EngineConfig
    {
        friend class Engine; // So only Engine can access Instance creation and deletion
        
        static EngineConfig* mInstance;
    
        // Window parameters
        std::string mWindowName;
        char mWindowFlags;
        unsigned int mWindowInitialWidth;
        unsigned int mWindowInitialHeight;
        int mInitialFpsLimit;
        bool mInitialVsync;
    
        // Logging
        bool mEventLogging;
        int mEventLogMask;
        
        // Console
        int mConsoleLevelMask;
        
        // ------------------
        
        explicit EngineConfig(const std::string& path);
        ~EngineConfig() = default;
        
        static EngineConfig* initInstance(const std::string& configPath) { mInstance = new EngineConfig(configPath); return mInstance; }
        static void closeInstance() { delete mInstance; mInstance = nullptr; }
        
    public:
        /** If it returns nullptr wait until engine initialize the instance */
        static EngineConfig* getInstance() { return mInstance; }
        
        [[nodiscard]] std::string getWindowName() const { return mWindowName; }
        [[nodiscard]] char getWindowFlags() const { return mWindowFlags; }
        [[nodiscard]] unsigned int getWindowInitialWidth() const { return mWindowInitialWidth; }
        [[nodiscard]] unsigned int getWindowInitialHeight() const { return mWindowInitialHeight; }
        [[nodiscard]] int getInitialFpsLimit() const { return mInitialFpsLimit; }
        [[nodiscard]] bool isInitialVsync() const { return mInitialVsync; }
        
        [[nodiscard]] bool isEventLogging() const { return mEventLogging; }
        [[nodiscard]] int getEventLogMask() const { return mEventLogMask; }
        
        [[nodiscard]] int getConsoleLevelMask() const { return mConsoleLevelMask; }
    };
}
