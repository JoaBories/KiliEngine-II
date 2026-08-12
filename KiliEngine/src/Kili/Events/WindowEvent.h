#pragma once
#include "klpch.h"
#include "Event.h"

namespace Kili
{
    class WindowCloseEvent : public IEvent
    {
    public:
        WindowCloseEvent() = default;
        
        [[nodiscard]] EventType getType() const override { return EventType::WindowClose; }
        [[nodiscard]] const char* getName() const override { return "Window close event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventWindow;}
    };
    
    class WindowResizeEvent : public IEvent
    {
    protected:
        unsigned int mWidth, mHeight;
        
    public:
        WindowResizeEvent(const unsigned int width, const unsigned int height) : 
            mWidth(width), mHeight(height) {}
        
        [[nodiscard]] EventType getType() const override { return EventType::WindowResize; }
        [[nodiscard]] const char* getName() const override { return "Window resize event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventWindow;}
        
        [[nodiscard]] std::string toString() const override
        {
            return "Window resize event : x : " + std::to_string(mWidth) + " y : " + std::to_string(mHeight);
        }
        
        [[nodiscard]] unsigned int getWidth() const { return mWidth; }
        [[nodiscard]] unsigned int getHeight() const { return mHeight; }
    };
    
    class WindowFocusUpdateEvent : public IEvent
    {
    protected:
        bool mGained;
        
    public:
        explicit WindowFocusUpdateEvent(const bool gained) :
            mGained(gained) {}
        
        [[nodiscard]] EventType getType() const override { return EventType::WindowFocus; }
        [[nodiscard]] const char* getName() const override { return "Window focus event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventWindow;}
        
        [[nodiscard]] std::string toString() const override
        {
            return "Window focus event : " + std::string(mGained ? "Gained" : "Lost");
        }
        
        [[nodiscard]] bool isGained() const { return mGained; }
    };
}