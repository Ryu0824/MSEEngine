#pragma once
#include "Event.h"

namespace MSE {

    class KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        virtual int GetCategoryFlags() const override
        {
            return EventCategoryKeyboard | EventCategoryInput;
        }

    protected:
        // 직접 생성할 수 없도록 protected 처리
        KeyEvent(int keycode) : m_KeyCode(keycode) {}
        int m_KeyCode;
    };

    // 1. 키 눌림 (반복 입력 포함)
    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {
        }

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        static EventType GetStaticType() { return EventType::KeyPressed; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "KeyPressed"; }

    private:
        int m_RepeatCount;
    };

    // 2. 키 뗌
    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        static EventType GetStaticType() { return EventType::KeyReleased; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "KeyReleased"; }
    };

    // 3. 문자 타이핑 (대소문자, 특수문자 등 실제 텍스트 입력용)
    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        static EventType GetStaticType() { return EventType::KeyTyped; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "KeyTyped"; }
    };
}