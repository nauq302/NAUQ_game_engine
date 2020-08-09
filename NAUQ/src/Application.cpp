//
// Created by nauq302 on 05/08/2020.
//

#include "nauq/Application.hpp"
#include "nauq/Log.hpp"



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

            for (Layer* layer : layerStack) {
                layer->onUpdate();
            }

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

        for (auto rit = layerStack.rbegin(); rit != layerStack.rend(); ++rit) {
            (*rit)->onEvent(event);
            if (event.isHandled()) {
                break;
            }
        }
    }

    /**
     *
     * @param layer
     */
    void Application::pushLayer(Layer* layer)
    {
        layerStack.pushLayer(layer);
    }

    /**
     *
     * @param layer
     */
    void Application::pushOverlay(Layer* layer)
    {
        layerStack.popOverlay(layer);
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