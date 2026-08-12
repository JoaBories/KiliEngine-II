#pragma once
#include "klpch.h"
#include "Event.h"

namespace Kili
{
    class AppCloseEvent : public IEvent
    {
    public:
        AppCloseEvent() = default;
        
        [[nodiscard]] EventType getType() const override { return EventType::AppClose; }
        [[nodiscard]] const char* getName() const override { return "App close event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventApp;}
    };
}