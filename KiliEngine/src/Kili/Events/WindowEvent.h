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
        [[nodiscard]] int getCategoryFlags() const override { return EventWindow;}
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
        [[nodiscard]] int getCategoryFlags() const override { return EventWindow;}
        
        [[nodiscard]] unsigned int getWidth() const { return mWidth; }
        [[nodiscard]] unsigned int getHeight() const { return mHeight; }
    };
    
    class WindowFocusEvent : public Event
    {
    public:
        WindowFocusEvent() = default;
        
        [[nodiscard]] EventType getType() const override { return EventType::WindowFocus; }
        [[nodiscard]] const char* getName() const override { return "Window focus event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventWindow;}
    };
    
    class WindowLostFocusEvent : public Event
    {
    public:
        WindowLostFocusEvent() = default;
        
        [[nodiscard]] EventType getType() const override { return EventType::WindowLostFocus; }
        [[nodiscard]] const char* getName() const override { return "Window lost focus event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventWindow;}
    };
}