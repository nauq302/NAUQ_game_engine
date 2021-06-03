//
// Created by nauq302 on 07/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_WINDOW_HPP
#define NAUQ_GAME_ENGINE_WINDOW_HPP


#include "nauq/core/Core.hpp"
#include "events/Event.hpp"

namespace nauq {

    /**
     *
     */
    struct WindowProps
    {
        std::string title;
        uint32_t width;
        uint32_t height;

        explicit WindowProps(const std::string& title = "Nauq Engine", uint32_t width = 1600, uint32_t height = 900) :
                title(title), width(width), height(height) {}
    };

    /**
     *
     */
    class NAUQ_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void onUpdate() = 0;

        [[nodiscard]] virtual uint32_t getWidth() const = 0;
        [[nodiscard]] virtual uint32_t getHeight() const = 0;

        [[nodiscard]] virtual void* getNativeWindow() const = 0;

        /// Window attribute
        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void setVSync(bool enable) = 0;
        [[nodiscard]] virtual bool isVSync() const = 0;

        static Scope<Window> create(const WindowProps& props = WindowProps());
    };
}

#endif //NAUQ_GAME_ENGINE_WINDOW_HPP
