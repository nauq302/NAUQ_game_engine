//
// Created by nauq302 on 06/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_APPLICATIONEVENT_HPP
#define NAUQ_GAME_ENGINE_APPLICATIONEVENT_HPP

#include "../Core.hpp"
#include "Event.hpp"

namespace nauq {

    class NAUQ_API WindowResizeEvent :
            public Event
    {
    private:
        unsigned int width, height;

    public:
        explicit inline WindowResizeEvent(unsigned width, unsigned height) : width(width), height(height) {}

    public:
        [[nodiscard]] inline unsigned int getWidth() const { return width; }
        [[nodiscard]] inline unsigned int getHeight() const { return height; }

        [[nodiscard]] std::string toString() const override
        {
            std::stringstream ss;
            ss << getName() << ": " << width << ", " << height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WINDOW_RESIZE)
        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    };

    class NAUQ_API WindowCloseEvent :
            public Event
    {
    private:
        unsigned int width, height;

    public:
        explicit inline WindowCloseEvent(unsigned width, unsigned height) : width(width), height(height) {}

    public:
        EVENT_CLASS_TYPE(WINDOW_CLOSE)
        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    };

    class NAUQ_API AppTickEvent :
            public Event
    {
    public:
        explicit inline AppTickEvent() = default;

    public:
        EVENT_CLASS_TYPE(APP_TICK)
        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    };

    class NAUQ_API AppUpdateEvent :
            public Event
    {
    public:
        explicit inline AppUpdateEvent() = default;

    public:
        EVENT_CLASS_TYPE(APP_UPDATE)
        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    };

    class NAUQ_API AppRenderEvent :
            public Event
    {
    public:
        explicit inline AppRenderEvent() = default;

    public:
        EVENT_CLASS_TYPE(APP_RENDER)
        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    };
}



#endif //NAUQ_GAME_ENGINE_APPLICATIONEVENT_HPP
