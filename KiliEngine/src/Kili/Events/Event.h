#pragma once

#include "klpch.h"

namespace Kili
{
    enum class EventType : char
    {
        AppClose,
        
        WindowClose,
        WindowResize,
        WindowFocus,
        
        Input
    };
    
    enum EventCategory : int
    {
        EventApp        = 1 << 0,
        EventWindow     = 1 << 1,
        EventInput      = 1 << 2,
        EventKeyboard   = 1 << 3,
        EventMouse      = 1 << 4,
        EventGamepad    = 1 << 5,
    };
    
    class IEvent
    {
    public:
        [[nodiscard]] virtual EventType getType() const = 0;
        [[nodiscard]] virtual const char* getName() const = 0;
        [[nodiscard]] virtual int getCategoryFlags() const = 0;
        
        /** Used for Debug and logging **/
        [[nodiscard]] virtual std::string toString() const { return getName(); }
        
        /** Return true if the category is present. **/
        [[nodiscard]] bool hasCategory(const EventCategory category) const { return getCategoryFlags() & category; }
        /** Return true if at least one category is present. **/
        [[nodiscard]] bool hasCategories(const int categories) const { return (getCategoryFlags() & categories) != 0; }
    };
    
}
