#include "klpch.h"
#include "EventDispatcher.h"

#include "Kili/Logger/Log.h"

Kili::IEventListener::IEventListener(const int categoryFilter) :
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
    for (EventCategory cat : AllCategories)
    {
        if (listener->mCategoryFilter & cat)
        {
            if (mListeners.find(cat) != mListeners.end()) mListeners.at(cat).push_back(listener);
            else mListeners.at(cat) = {listener};
        }
    }
}

void Kili::EventDispatcher::removeListener(const IEventListener* listener)
{
    for (EventCategory cat : AllCategories)
    {
        if (listener->mCategoryFilter & cat)
        {
            if (mListeners.find(cat) == mListeners.end()) break;
            if (const auto iter = std::find(mListeners.at(cat).begin(), mListeners.at(cat).end(), listener); iter != mListeners.at(cat).end()) // find listener in vector
            {
                mListeners.at(cat).erase(iter);
            }
        }
    }
}

void Kili::EventDispatcher::receiveEvent(const Event& event)
{
    for (const auto& [category, listeners] : mListeners)
    {
        if (event.isInCategory(category))
        {
            for (IEventListener* listener : listeners)
            {
                listener->onEvent(event);
            }
        }
    }
    
    // DIST to remove for distribution
    if (mLogging)
    {
        if (event.getCategoryFlags() & mCategoryFilter) return;
        LOG_DEBUG(event.toString());
    }
}