#include "klpch.h"
#include "EventDispatcher.h"

#include "Kili/Logger/Log.h"

Kili::IEventListener::IEventListener(const char categoryFilter) :
    mCategoryFilter(categoryFilter)
{
    EventDispatcher::instance().addListener(this);
}

Kili::IEventListener::~IEventListener()
{
    EventDispatcher::instance().removeListener(this);
}

void Kili::EventDispatcher::addListener(IEventListener* listener)
{
    if (const auto it = find(mListeners.begin(), mListeners.end(), listener); 
        it == mListeners.end()) mListeners.push_back(listener);
}

void Kili::EventDispatcher::removeListener(const IEventListener* listener)
{
    if (const auto it = find(mListeners.begin(), mListeners.end(), listener); 
        it != mListeners.end()) mListeners.erase(it);
}

void Kili::EventDispatcher::receiveEvent(const Event& event) const
{
    for (IEventListener* listener : mListeners)
    {
        if (event.hasCategories(listener->mCategoryFilter)) listener->onEvent(event);
    }
    
    // DIST to remove for distribution
    if (mLogging)
    {
        if (event.hasCategories(mCategoryFilter)) return;
        LOG_DEBUG(event.toString());
    }
}
