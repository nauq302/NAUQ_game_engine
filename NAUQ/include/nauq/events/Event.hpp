//
// Created by nauq302 on 06/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_EVENT_HPP
#define NAUQ_GAME_ENGINE_EVENT_HPP

#include <functional>
#include "nauq/core/Core.hpp"
#include "nauq/Log.hpp"

namespace nauq {

    /**
     *  @enum EventType
     *
     *  @brief Enum to specify each Event Type
     */
    enum class EventType
    {
        NONE,
        WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVE,
        APP_TICK, APP_UPDATE, APP_RENDER,
        KEY_PRESS, KEY_RELEASE, KEY_TYPE,
        MOUSE_BUTTON_PRESS, MOUSE_BUTTON_RELEASE, MOUSE_MOVE, MOUSE_SCROLL,
    };


    /**
     *  @enum EventCategory
     *
     *  @brief Enum to specify of each Event Category
     */
    enum EventCategory : unsigned char
    {
        NONE                        = 0,            // 0b 00000000
        EVENT_CATEGORY_APPLICATION  = bit(0), // 0b 00000001
        EVENT_CATEGORY_INPUT        = bit(1), // 0b 00000010
        EVENT_CATEGORY_KEYBOARD     = bit(2), // 0b 00000100
        EVENT_CATEGORY_MOUSE        = bit(3), // 0b 00001000
        EVENT_CATEGORY_MOUSE_BUTTON = bit(4), // 0b 00010000
    };


    /**
     *  @brief A bunch of functions to specify Type of each Event
     */
#define EVENT_CLASS_TYPE(type) \
    static inline EventType getStaticType() { return EventType::type; } \
    inline EventType getEventType() const override { return getStaticType(); } \
    inline const char* getName() const override { return #type; }


    /**
     *  @brief A bunch of functions to specify Category Flags of each Event
     */
#define EVENT_CLASS_CATEGORY(category) \
    inline unsigned int getCategoryFlag() const override { return category; }


    /**
     *  @class Event
     *
     *  @brief Base class for pre-defined some properties and methods of every Event
     *
     *
     */
    class NAUQ_API Event
    {
        friend class EventDispatcher;

    public:
        bool handled = false;

    public:
        virtual ~Event() = default;

        [[nodiscard]] virtual EventType getEventType() const = 0;
        [[nodiscard]] virtual const char* getName() const = 0;
        [[nodiscard]] virtual unsigned int getCategoryFlag() const = 0;
        [[nodiscard]] virtual std::string toString() const { return getName(); }
        [[nodiscard]] inline bool isInCategory(EventCategory category) const { return category & getCategoryFlag(); }
        [[nodiscard]] inline bool isHandled() const { return handled; }
    };


    /**
     *  @operator <<
     *
     *  @brief Push Event's name to ostream
     *
     *  @param os: The ostream where to push
     *  @param event: The event to push its name into ostream
     *  @return The ostream where to push
     */
    inline std::ostream& operator <<(std::ostream& os, const Event& event) { return os << event.toString(); }


    /**
     *  @concept EventDerived
     *
     *  @brief Determine the specific type T is derived from Event or not
     *
     *  @tparam T: Type need to determine
     */
    template<typename T>
    concept EventDerived = std::derived_from<T,Event>;


    /**
     *  @class EventDispatcher
     *
     *  @brief Use to dispatch events, one EventDispatcher can only dispatch one event
     */
    class NAUQ_API EventDispatcher
    {
        /**
         *
         */
        template<EventDerived E>
        using EventFn = std::function<bool(E&)>;

    private:
        /**
         *  @property event
         *  @type reference to Event
         *  @brief The event need to be dispatched
         */
        Event& event;

    public:
        /**
         *  @constructor
         *
         *  @brief Set event to dispatch
         *
         *  @param event
         */
        explicit inline EventDispatcher(Event& event) : event(event) {}

    public:
        /**
         *  @method dispatch
         *
         *  @brief dispatch the event
         *
         *  @tparam E
         *  @param func
         *  @return
         */
        template<EventDerived E>
        bool dispatch(const EventFn<E>& func)
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
