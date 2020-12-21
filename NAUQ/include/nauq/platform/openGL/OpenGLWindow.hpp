//
// Created by nauq302 on 07/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLWINDOW_HPP
#define NAUQ_GAME_ENGINE_OPENGLWINDOW_HPP

#include "nauq/Window.hpp"
#include "nauq/renderer/GraphicsContext.hpp"
#include "GLFW/glfw3.h"

namespace nauq {

    /**
     * @class OpenGLWindow
     *
     * @inherit Window
     *
     * @brief Window object for OpenGL Platform
     */
    class OpenGLWindow :
            public Window
    {
    private:
        struct WindowData {
            std::string title;
            unsigned width, height;
            bool vSync;
            EventCallbackFn eventCallback;
        };

        GLFWwindow* window;
        WindowData data;
        GraphicsContext* context;

    public:
        explicit OpenGLWindow(const WindowProps& props);
        ~OpenGLWindow() override;

    public:
        void onUpdate() override;
        [[nodiscard]] inline unsigned int getWidth() const override { return data.width; }
        [[nodiscard]] inline unsigned int getHeight() const override { return data.height; }

        [[nodiscard]] inline void* getNativeWindow() const override { return window; }

        inline void setEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback; }
        void setVSync(bool enable) override;
        [[nodiscard]] bool isVSync() const override;

    private:
        void init(const WindowProps& props);
        void shutdown();
    };


}


#endif //NAUQ_GAME_ENGINE_OPENGLWINDOW_HPP
