//
// Created by nauq302 on 06/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_KEYEVENT_HPP
#define NAUQ_GAME_ENGINE_KEYEVENT_HPP

#include "Event.hpp"

namespace nauq {

    /**
     *
     */
    class NAUQ_API KeyEvent :
            public Event
    {
    protected:
        int keycode;

    protected:
        explicit KeyEvent(int keycode) : keycode(keycode) {}

    public:
        [[nodiscard]] inline int getKeyCode() const { return keycode; }
        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT)
    };

    /**
     *
     */
    class NAUQ_API KeyPressEvent :
            public KeyEvent
    {
    private:
        int repeatCount;

    public:
        explicit KeyPressEvent(int keycode, int repeatCount) : KeyEvent(keycode), repeatCount(repeatCount) {}

    public:
        [[nodiscard]] inline int getRepeatCount() const { return repeatCount; }
        [[nodiscard]] std::string toString() const override
        {
            std::stringstream ss;
            ss << getName() << ": " << keycode << " (" << repeatCount << " repeats)";
            return ss.str();
        }
        EVENT_CLASS_TYPE(KEY_PRESS)
    };

    /**
     *
     */
    class NAUQ_API KeyReleaseEvent :
            public KeyEvent
    {
    public:
        explicit KeyReleaseEvent(int keycode) : KeyEvent(keycode) {}

    public:
        [[nodiscard]] std::string toString() const override
        {
            std::stringstream ss;
            ss << getName() << ": " << keycode;
            return ss.str();
        }
        EVENT_CLASS_TYPE(KEY_RELEASE)
    };
}


#endif //NAUQ_GAME_ENGINE_KEYEVENT_HPP
