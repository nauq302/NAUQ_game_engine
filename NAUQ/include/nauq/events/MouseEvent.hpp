//
// Created by nauq302 on 06/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_MOUSEEVENT_HPP
#define NAUQ_GAME_ENGINE_MOUSEEVENT_HPP

#include "Event.hpp"
#include "glm/vec2.hpp"

namespace nauq {

    /**
     *
     */
    class NAUQ_API MouseMoveEvent :
            public Event
    {
    private:
        glm::vec2 position;

    public:
        explicit inline MouseMoveEvent(float x, float y) : position{ x, y } {}

    public:
        [[nodiscard]] inline float getX() const { return position.x; }
        [[nodiscard]] inline float getY() const { return position.y; }
        [[nodiscard]] std::string toString() const override
        {
            std::stringstream ss;
            ss << getName() << ": " << position.x << ", " << position.y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MOUSE_MOVE)
        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)
    };

    /**
     *
     */
    class NAUQ_API MouseScrollEvent :
            public Event
    {
    private:
        glm::vec2 offset;

    public:
        explicit inline MouseScrollEvent(float x, float y) : offset{ x, y } {}

    public:
        [[nodiscard]] inline float getXOffset() const { return offset.x; }
        [[nodiscard]] inline float getYOffset() const { return offset.y; }
        [[nodiscard]] std::string toString() const override
        {
            std::stringstream ss;
            ss << getName() << ": " << offset.x << ", " << offset.y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MOUSE_SCROLL)
        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)
    };

    /**
     *
     */
    class NAUQ_API MouseButtonEvent :
            public Event
    {
    protected:
        int button;

    public:
        explicit inline MouseButtonEvent(int button) : button(button) {}

    public:
        [[nodiscard]] inline int getMouseButton() const { return button; }
        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE_BUTTON | EVENT_CATEGORY_INPUT)
    };

    /**
     *
     */
    class NAUQ_API MouseButtonPressEvent :
            public MouseButtonEvent
    {
    public:
        explicit inline MouseButtonPressEvent(int button) : MouseButtonEvent(button) {}

    public:
        [[nodiscard]] std::string toString() const override
        {
            std::stringstream ss;
            ss << getName() << ": " << button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESS)
    };

    /**
     *
     */
    class NAUQ_API MouseButtonReleaseEvent :
            public MouseButtonEvent
    {
    public:
        explicit inline MouseButtonReleaseEvent(int button) : MouseButtonEvent(button) {}

    public:
        [[nodiscard]] std::string toString() const override
        {
            std::stringstream ss;
            ss << getName() << ": " << button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASE)
    };
}

#endif //NAUQ_GAME_ENGINE_MOUSEEVENT_HPP
