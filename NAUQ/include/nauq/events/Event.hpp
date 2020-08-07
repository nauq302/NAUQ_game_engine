//
// Created by nauq302 on 06/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_EVENT_HPP
#define NAUQ_GAME_ENGINE_EVENT_HPP

#include "../Core.hpp"

namespace nauq {

    /**
     *
     * @param c
     * @return
     */
    constexpr unsigned char bit(unsigned char c) { return 1u << c; }

    /**
     *
     */
    enum class EventType
    {
        NONE,
        WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVE,
        APP_TICK, APP_UPDATE, APP_RENDER,
        KEY_PRESS, KEY_RELEASE,
        MOUSE_BUTTON_PRESS, MOUSE_BUTTON_RELEASE, MOUSE_MOVE, MOUSE_SCROLL,
    };

    /**
     *
     */
    enum EventCategory : unsigned char
    {
        NONE = 0,
        EVENT_CATEGORY_APPLICATION  = bit(0),
        EVENT_CATEGORY_INPUT        = bit(1),
        EVENT_CATEGORY_KEYBOARD     = bit(2),
        EVENT_CATEGORY_MOUSE        = bit(3),
        EVENT_CATEGORY_MOUSE_BUTTON = bit(4),
    };


#define EVENT_CLASS_TYPE(type) \
    static inline EventType getStaticType() { return EventType::type; } \
    inline EventType getEventType() const override { return getEventType(); } \
    inline const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual inline unsigned int getCategoryFlag() const override { return category; }


    /**
     *
     */
    class NAUQ_API Event
    {
        friend class EventDispatcher;

    protected:
        bool handled = false;

    public:
        [[nodiscard]] virtual EventType getEventType() const = 0;
        [[nodiscard]] virtual const char* getName() const = 0;
        [[nodiscard]] virtual unsigned int getCategoryFlag() const = 0;
        [[nodiscard]] virtual std::string toString() const { return getName(); }
        [[nodiscard]] inline bool isInCategory(EventCategory category) const { return category & getCategoryFlag(); }
    };

    /**
     *
     * @tparam T
     */
    template<typename T>
    concept EventDerived = std::derived_from<T,Event>;

    /**
     *
     */
    class NAUQ_API EventDispatcher
    {
        template<EventDerived E>
        using EventFn = std::function<bool(E&)>;

    private:
        Event& event;

    public:
        explicit inline EventDispatcher(Event& event) : event(event) {}

    public:
        template<EventDerived E>
        bool dispatch(EventFn<E> func)
        {
            if (event.getEventType() == E::getStaticType()) {
                event.handled = func(static_cast<E&>(event));
                return true;
            }

            return false;
        }
    };
}

#endif //NAUQ_GAME_ENGINE_EVENT_HPP
