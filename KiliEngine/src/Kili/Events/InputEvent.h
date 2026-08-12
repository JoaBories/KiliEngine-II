#pragma once
#include "klpch.h"
#include "Event.h"

namespace Kili
{
    enum class InputType : Uint8
    {
        Keyboard,
        
        MouseButton,
        MouseMove,
        MouseWheel,
        
        GamepadButton,
        GamepadAxis,
    };
    
    class InputEvent : public Event
    {
    public:
        [[nodiscard]] EventType getType() const override { return EventType::Input; }
        
        [[nodiscard]] virtual InputType getInputType() const = 0;
    };
    
    class KeyInputEvent : public InputEvent
    {
    protected:
        SDL_Keycode mKey;
        bool mDown;
        
    public:
        KeyInputEvent(const SDL_Keycode keycode, const bool down) : 
            mKey(keycode), mDown(down) {}

        [[nodiscard]] const char* getName() const override { return "Key input event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventInput | EventKeyboard; }
        
        [[nodiscard]] std::string toString() const override
        {
            return "Key input event : " + std::to_string(mKey) + (mDown ? " Down" : " Up");
        }
        
        [[nodiscard]] InputType getInputType() const override { return InputType::Keyboard; }
        
        [[nodiscard]] SDL_Keycode getKey() const { return mKey; }
        [[nodiscard]] bool isDown() const { return mDown; }
    };
    
    class MouseButtonInputEvent : public InputEvent
    {
    protected:
        Uint8 mButton;
        bool mDown;
        Vector2 mMousePos;
        Uint8 mClicks;

    public:
        MouseButtonInputEvent(const Uint8 button, const bool down, const Vector2 mousePos, const Uint8 clicks) :
            mButton(button), mDown(down), mMousePos(mousePos), mClicks(clicks) {}
        
        [[nodiscard]] const char* getName() const override { return "Mouse button input event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventInput | EventMouse; }
        
        [[nodiscard]] std::string toString() const override
        {
            return "Mouse button input event : " + std::to_string(mButton) + (mDown ? " Down" : " Up") + " at " + mMousePos.toString() + " / " + std::to_string(mClicks);
        }
        
        [[nodiscard]] InputType getInputType() const override { return InputType::MouseButton; }
        
        /** Return an unsigned int with the index of the button.\n 1 is left, 2 is middle and 3 is right */
        [[nodiscard]] Uint8 getButton() const { return mButton; }
        [[nodiscard]] bool isDown() const { return mDown; }
        [[nodiscard]] Vector2 getMousePos() const { return mMousePos; }
        [[nodiscard]] Uint8 getClicks() const { return mClicks; }
    };
    
    class MouseMoveInputEvent : public InputEvent
    {
    protected:
        Vector2 mMousePos;
        Vector2 mMouseMove;
        
    public:
        MouseMoveInputEvent(const Vector2 mousePos, const Vector2 mouseMove) : 
            mMousePos(mousePos), mMouseMove(mouseMove) {}
        
        [[nodiscard]] const char* getName() const override { return "Mouse movement input event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventInput | EventMouse; }
        
        [[nodiscard]] std::string toString() const override
        {
            return "Mouse move input event : " + mMousePos.toString() + " / " + mMouseMove.toString();
        }
        
        [[nodiscard]] InputType getInputType() const override { return InputType::MouseMove; }
        
        [[nodiscard]] Vector2 getMousePos() const { return mMousePos; }
        [[nodiscard]] Vector2 getMouseMove() const { return mMouseMove; }
    };
    
    class MouseWheelInputEvent : public InputEvent
    {
    protected:
        float mMouseScrollX, mMouseScrollY;
        Vector2 mMousePos;
        bool mFlipped;
        
    public:
        MouseWheelInputEvent(const float mouseScrollX, const float mouseScrollY, const Vector2 mousePos, const bool flipped) : 
            mMouseScrollX(mouseScrollX), mMouseScrollY(mouseScrollY), mMousePos(mousePos), mFlipped(flipped) {}
        
        [[nodiscard]] const char* getName() const override { return "Mouse wheel input event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventInput | EventMouse; }
        
        [[nodiscard]] std::string toString() const override
        {
            return "Mouse wheel input event : x : " + std::to_string(mMouseScrollX) + " y : " + std::to_string(mMouseScrollY) + " / " + mMousePos.toString();
        }
        
        [[nodiscard]] InputType getInputType() const override { return InputType::MouseWheel; }
        
        [[nodiscard]] float getMouseScrollX() const { return mMouseScrollX; } /* Right positive, left negative. */
        [[nodiscard]] float getMouseScrollY() const { return mMouseScrollY; } /* Away from the user positive, toward the user negative. */
        [[nodiscard]] Vector2 getMousePos() const { return mMousePos; }
        [[nodiscard]] bool isFlipped() const { return mFlipped; }
    };
    
    class GamepadButtonInputEvent : public InputEvent
    {
    protected:
        SDL_GamepadButton mGamepadButton;
        bool mDown;
        
    public:
        GamepadButtonInputEvent(const Uint8 button, const bool down) : 
            mGamepadButton(static_cast<SDL_GamepadButton>(button)), mDown(down) {}
        
        [[nodiscard]] const char* getName() const override { return "Gamepad button input event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventInput | EventGamepad; }
        
        [[nodiscard]] std::string toString() const override
        {
            return "Gamepad button input event : " + std::to_string(mGamepadButton) + " / " + (mDown ? " Down" : " Up");
        }
        
        [[nodiscard]] InputType getInputType() const override { return InputType::GamepadButton; }
        
        [[nodiscard]] SDL_GamepadButton getGamepadButton() const { return mGamepadButton; }
        [[nodiscard]] bool isDown() const { return mDown; }
    };
    
    class GamepadAxisInputEvent : public InputEvent
    {
    protected:
        SDL_GamepadAxis mGamepadAxis;
        Sint16 mGamepadAxisValue;
        
    public:
        GamepadAxisInputEvent(const Uint8 axis, const Sint16 axisValue) : 
            mGamepadAxis(static_cast<SDL_GamepadAxis>(axis)), mGamepadAxisValue(axisValue) {}
        
        [[nodiscard]] const char* getName() const override { return "Gamepad axis input event"; }
        [[nodiscard]] int getCategoryFlags() const override { return EventInput | EventGamepad; }
        
        [[nodiscard]] std::string toString() const override
        {
            return "Gamepad axis input event : " + std::to_string(mGamepadAxis) + " / " + std::to_string(getGamepadAxisValueNormalized());
        }
        
        [[nodiscard]] InputType getInputType() const override { return InputType::GamepadAxis; }
        
        [[nodiscard]] SDL_GamepadAxis getGamepadAxis() const { return mGamepadAxis; }
        /** Scaling from -32768 to 32768. (IDK this is a SDL3 thing)*/
        [[nodiscard]] Sint16 getGamepadAxisValue() const { return mGamepadAxisValue; }
        [[nodiscard]] float getGamepadAxisValueNormalized() const { return static_cast<float>(mGamepadAxisValue) / 32768.0f; }
    };
}