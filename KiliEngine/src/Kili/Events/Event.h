#pragma once

#include "klpch.h"

namespace Kili
{
    enum class EventType
    {
        None = 0,
        
        WindowClose,
        WindowResize,
        WindowFocus,
        
        Input
    };
    
    enum EventCategory
    {
        EventNone = 0,
        EventWindow     = 1 << 0,
        EventInput      = 1 << 1,
        EventKeyboard   = 1 << 2,
        EventMouse      = 1 << 3,
        EventGamepad    = 1 << 4,
    };

    constexpr EventCategory AllCategories[] = {EventWindow, EventInput, EventKeyboard, EventMouse, EventGamepad};
    
    class Event
    {
    public:
        [[nodiscard]] virtual EventType getType() const = 0;
        [[nodiscard]] virtual const char* getName() const = 0;
        [[nodiscard]] virtual int getCategoryFlags() const = 0;
        
        [[nodiscard]] virtual std::string toString() const { return getName(); }
        
        [[nodiscard]] bool isInCategory(const EventCategory category) const { return getCategoryFlags() & category; }
    };
    
}
