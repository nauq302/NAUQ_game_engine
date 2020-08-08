//
// Created by nauq302 on 05/08/2020.
//

#include "nauq/Application.hpp"
#include "nauq/Log.hpp"

#include <GLFW/glfw3.h>

namespace nauq {

#define BIND_EVENT_FN(fn) std::bind_front(&Application::fn, this)

    /**
     *
     */
    Application::Application() :
        window(Window::create()),
        running(true)
    {
        window->setEventCallback(BIND_EVENT_FN(onEvent));
    }

    /**
     *
     */
    Application::~Application() = default;

    /**
     *
     */
    void Application::run()
    {
        while (running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            window->onUpdate();
        }
    }

    /**
     *
     * @param event
     */
    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClosed));

        NAUQ_CORE_INFO("{0}", event.toString());
    }

    /**
     *
     * @param event
     * @return
     */
    bool Application::onWindowClosed(WindowCloseEvent& event)
    {
        running = false;
        return true;
    }
}