//
// Created by nauq302 on 05/08/2020.
//

#include "nauq/Application.hpp"

#include <memory>
#include "nauq/Log.hpp"
#include "nauq/imGui/ImGuiLayer.hpp"
#include "nauq/Input.hpp"
#include "nauq/renderer/Renderer.hpp"


namespace nauq {

    /**
     *
     */
    Application::Application() :
        lastFrameTime(0.f),
        running(true)
    {
        NQ_CORE_ASSERT(instance == nullptr, "Application already exists");
        instance = this;

        window.reset(Window::create());
        window->setEventCallback(NQ_BIND_EVENT_FN(Application::onEvent));

        Renderer::init();

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);

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

            auto time = static_cast<float>(glfwGetTime());
            TimeStep timeStep = time - lastFrameTime;
            lastFrameTime = time;

            for (Layer* l : layerStack) {
                l->onUpdate(timeStep);
            }

            imGuiLayer->begin();
            for (Layer* l : layerStack) {
                l->onImGuiRender();
            }
            imGuiLayer->end();

#ifdef NAUQ_DEBUG
            glm::vec2 mousePos = Input::getMousePosition();
            NAUQ_CORE_TRACE("{0}, {1}", mousePos.x, mousePos.y);
#endif

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

        dispatcher.dispatch<WindowCloseEvent>(NQ_BIND_EVENT_FN(Application::onWindowClosed));

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
        layer->onAttach();
    }

    /**
     *
     * @param layer
     */
    void Application::pushOverlay(Layer* layer)
    {
        layerStack.pushOverlay(layer);
        layer->onAttach();
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