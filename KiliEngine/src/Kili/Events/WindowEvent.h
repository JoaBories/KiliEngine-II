#pragma once
#include "klpch.h"
#include "Event.h"

namespace Kili
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;
        
        [[nodiscard]] EventType getType() const override { return EventType::WindowClose; }
        [[nodiscard]] const char* getName() const override { return "Window close event"; }
        [[nodiscard]] char getCategoryFlags() const override { return EventWindow;}
    };
    
    class WindowResizeEvent : public Event
    {
    protected:
        unsigned int mWidth, mHeight;
        
    public:
        WindowResizeEvent(const unsigned int width, const unsigned int height) : 
            mWidth(width), mHeight(height) {}
        
        [[nodiscard]] EventType getType() const override { return EventType::WindowResize; }
        [[nodiscard]] const char* getName() const override { return "Window resize event"; }
        [[nodiscard]] char getCategoryFlags() const override { return EventWindow;}
        
        [[nodiscard]] std::string toString() const override
        {
            return "Window resize event : x : " + std::to_string(mWidth) + " y : " + std::to_string(mHeight);
        }
        
        [[nodiscard]] unsigned int getWidth() const { return mWidth; }
        [[nodiscard]] unsigned int getHeight() const { return mHeight; }
    };
    
    class WindowFocusUpdateEvent : public Event
    {
    protected:
        bool mGained;
        
    public:
        explicit WindowFocusUpdateEvent(const bool gained) :
            mGained(gained) {}
        
        [[nodiscard]] EventType getType() const override { return EventType::WindowFocus; }
        [[nodiscard]] const char* getName() const override { return "Window focus event"; }
        [[nodiscard]] char getCategoryFlags() const override { return EventWindow;}
        
        [[nodiscard]] std::string toString() const override
        {
            return "Window focus event : " + std::string(mGained ? "Gained" : "Lost");
        }
        
        [[nodiscard]] bool isGained() const { return mGained; }
    };
}