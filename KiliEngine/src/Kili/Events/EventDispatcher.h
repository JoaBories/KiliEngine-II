#pragma once
#include "Event.h"

namespace Kili
{
    class IEventListener
    {
        friend class EventDispatcher;
        
    protected:
        int mCategoryFilter;

        explicit IEventListener(int categoryFilter);
        ~IEventListener();
        
        virtual void onEvent(const Event& event) = 0;
    };
    
    class EventDispatcher
    {
    private:
        std::unordered_map<EventCategory, std::vector<IEventListener*>> mListeners;
        bool mLogging;
        
        EventDispatcher() = default;
        ~EventDispatcher() { mListeners.clear(); }
        
    public:
        static EventDispatcher& instance()
        {
            static EventDispatcher instance;
            return instance;
        }
        
        EventDispatcher(const EventDispatcher&) = delete;
        EventDispatcher& operator=(const EventDispatcher&) = delete;
        
        void addListener(IEventListener* listener);
        void removeListener(const IEventListener* listener);
        
        void receiveEvent(const Event& event);
        
        void setLoggingEvent(const bool logging) { mLogging = logging; }
    };
} 
