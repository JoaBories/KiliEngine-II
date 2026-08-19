#pragma once

// Apparently the app is locked at 5 millions fps with unlimited fps. I don't if it comes from windows, Sdl3, or my code.
// Not a big problem as it is quite hard to reach with actual code in the loop, I reached 5m with only polling Sdl3 events.

namespace Kili
{
    class TimeClock
    {
        friend class Engine; // So only Engine can access Clocking methods

        unsigned long long mFrameStart; /* Tick from Sdl clock */
        
        unsigned long long mFrameTime;
        unsigned long long mLastFrameStart;
        
        static const unsigned long long SdlFrequency; /* From Sdl clock frequency. Usually return 10,000,000 on Windows so 10 tick is 1 micro seconds. */
        unsigned int mMaxFps;
        unsigned long long mTicksPerFrame; /* Number of tick for each frame to pass. Only used if fps are capped and vsync off. */
        
        static unsigned long long mTime; /* Time elapsed since app start. */
        static unsigned int mFrameCount; /* Number of frame since app start */
        
        float mMaxDeltaTime;
        static float mDeltaTime;
        
        bool mLogging;
        float mLogInterval;
        double mLastLog;

        explicit TimeClock(unsigned int maxFps = 60, float maxDeltaTime = 1.0f);
        ~TimeClock() = default;
        
        void computeTime();
        void delayTime() const;
        
    public:
        // Rule of zero
        TimeClock(const TimeClock&) = delete;
        TimeClock& operator=(const TimeClock&) = delete;
        TimeClock(TimeClock&& pOther) noexcept = delete;
        TimeClock& operator=(TimeClock&& pOther) noexcept = delete;

        [[nodiscard]] bool getLogging() const { return mLogging; }
        void setLogging(const bool logging) { mLogging = logging; }

        [[nodiscard]] float getLoggingInterval() const { return mLogInterval; }
        void setLoggingInterval(const float interval) { mLogInterval = interval; }
        
        static double time() { return static_cast<double>(mTime) / static_cast<double>(SdlFrequency); } /* Return elapsed since app start */
        static unsigned int frameCount() { return mFrameCount; } /* Return frame count since app start */
        static float deltaTime() { return mDeltaTime; } /* Delta time in second */
        
        static float avgFrameTime() { return static_cast<float>(mTime) / static_cast<float>(SdlFrequency) / static_cast<float>(mFrameCount); } /* Average frame time in second */
    };
}