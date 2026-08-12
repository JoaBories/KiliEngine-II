#include "klpch.h"
#include "EventDispatcher.h"

#include "AppEvent.h"
#include "InputEvent.h"
#include "WindowEvent.h"
#include "Kili/Logger/Log.h"

Kili::IEventListener::IEventListener(const int categoryFilter) :
    mCategoryFilter(categoryFilter)
{
    EventDispatcher::instance()->addListener(this);
}

Kili::IEventListener::~IEventListener()
{
    EventDispatcher::instance()->removeListener(this);
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

void Kili::EventDispatcher::pollSdlEvents() const
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_EVENT_QUIT:
                receiveEvent(AppCloseEvent());
                break;
                
            case SDL_EVENT_KEY_DOWN:
                receiveEvent(KeyInputEvent(event.key.key, true));
                break;
                
            case SDL_EVENT_KEY_UP:
                receiveEvent(KeyInputEvent(event.key.key, false));
                break;
                
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                receiveEvent(MouseButtonInputEvent(
                    event.button.button, true, 
                    Vector2{event.button.x, event.button.y}, 
                    event.button.clicks));
                break;
                
            case SDL_EVENT_MOUSE_BUTTON_UP:
                receiveEvent(MouseButtonInputEvent(
                    event.button.button, false, 
                    Vector2{event.button.x, event.button.y}, 
                    event.button.clicks));
                break;
                
            case SDL_EVENT_MOUSE_MOTION:
                receiveEvent(MouseMoveInputEvent(
                    Vector2{event.motion.x, event.motion.y}, 
                    Vector2{event.motion.xrel, event.motion.yrel}));
                break;
                
            case SDL_EVENT_MOUSE_WHEEL:
                receiveEvent(MouseWheelInputEvent(
                    event.wheel.x, 
                    event.wheel.y, 
                    Vector2{event.wheel.mouse_x, event.wheel.mouse_y}, 
                    event.wheel.direction));
                break;
                
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                receiveEvent(GamepadButtonInputEvent(event.gbutton.button, true));
                break;
                
            case SDL_EVENT_GAMEPAD_BUTTON_UP:
                receiveEvent(GamepadButtonInputEvent(event.gbutton.button, false));
                break;
                
            case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                receiveEvent(GamepadAxisInputEvent(event.gaxis.axis, event.gaxis.value));
                break;
                
            case SDL_EVENT_WINDOW_RESIZED:
                receiveEvent(WindowResizeEvent(event.window.data1, event.window.data2));
                break;
                
            case SDL_EVENT_WINDOW_FOCUS_GAINED:
                receiveEvent(WindowFocusUpdateEvent(true));
                break;
                
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                receiveEvent(WindowFocusUpdateEvent(false));
                break;
        }
    }
}

void Kili::EventDispatcher::receiveEvent(const IEvent& event) const
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
