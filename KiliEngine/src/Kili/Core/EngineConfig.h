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
        unsigned int mWindowWidth;
        unsigned int mWindowHeight;
        bool mVsync;
    
        // EventSystem
        bool mEventLogging;
        int mEventLogMask;
        
        // Console
        int mConsoleLevelMask;
        
        // Time
        unsigned int mMaxFps;
        float mMaxDeltaTime;
        bool mFpsLogging;
        float mFpsLogInterval;
        
        // ------------------
        
        explicit EngineConfig(const std::string& path);
        ~EngineConfig() = default;
        
        static EngineConfig* initInstance(const std::string& configPath) { mInstance = new EngineConfig(configPath); return mInstance; }
        static void closeInstance() { delete mInstance; mInstance = nullptr; }
        
    public:
        // Rule of zero
        EngineConfig(const EngineConfig&) = delete;
        EngineConfig& operator=(const EngineConfig&) = delete;
        EngineConfig(EngineConfig&& pOther) noexcept = delete;
        EngineConfig& operator=(EngineConfig&& pOther) noexcept = delete;
        
        /** If it returns nullptr wait until engine initialize the instance */
        static EngineConfig* getInstance() { return mInstance; }
        
        // Todo Implement setters to change parameters
        
        [[nodiscard]] std::string getWindowName() const { return mWindowName; }
        [[nodiscard]] char getWindowFlags() const { return mWindowFlags; }
        [[nodiscard]] unsigned int getWindowWidth() const { return mWindowWidth; }
        [[nodiscard]] unsigned int getWindowHeight() const { return mWindowHeight; }
        [[nodiscard]] bool isVsync() const { return mVsync; }
        
        [[nodiscard]] bool isEventLogging() const { return mEventLogging; }
        [[nodiscard]] int getEventLogMask() const { return mEventLogMask; }
        
        [[nodiscard]] int getConsoleLevelMask() const { return mConsoleLevelMask; }
        
        [[nodiscard]] unsigned int getMaxFps() const { return mMaxFps; }
        [[nodiscard]] float getMaxDeltaTime() const { return mMaxDeltaTime; }
        [[nodiscard]] bool isFpsLogging() const { return mFpsLogging; }
        [[nodiscard]] float getFpsLogInterval() const { return mFpsLogInterval; }
    };
}
