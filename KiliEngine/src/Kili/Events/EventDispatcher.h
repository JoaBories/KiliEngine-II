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
        
        virtual void onEvent(const IEvent& event) = 0;
    };
    
    class EventDispatcher
    {
    private:
        std::vector<IEventListener*> mListeners;
        
        // DIST to remove for distribution
        int mCategoryFilter; /* Prevent for logging event from these categories */
        bool mLogging;
        
        EventDispatcher() = default;
        ~EventDispatcher() { mListeners.clear(); }
        
    public:
        static EventDispatcher* instance()
        {
            static EventDispatcher instance;
            return &instance;
        }
        
        EventDispatcher(const EventDispatcher&) = delete;
        EventDispatcher& operator=(const EventDispatcher&) = delete;
        
        void addListener(IEventListener* listener);
        void removeListener(const IEventListener* listener);
        
        void pollSdlEvents() const;
        void receiveEvent(const IEvent& event) const;
        
        // DIST to remove for distribution
        void setLoggingEvent(const bool logging) { mLogging = logging; }
        void setLogFilter(const int categoryFilter) { mCategoryFilter = categoryFilter; } /* Prevent for logging event from these categories */
    };
} 
