//
// Created by nauq302 on 05/08/2020.
//

#include "nauq/core/Application.hpp"

#include <memory>
#include "nauq/core/Log.hpp"
#include "nauq/imGui/ImGuiLayer.hpp"
#include "nauq/core/Input.hpp"
#include "nauq/renderer/Renderer.hpp"
#include "nauq/debug/Instrumentor.hpp"

namespace nauq {

    /**
     *
     */
    Application::Application(const std::string& name) :
        lastFrameTime(0.f),
        running(true),
        minimized(false)
    {
        NQ_PROFILE_FUNCTION();

        NQ_CORE_ASSERT(instance == nullptr, "Application already exists");
        instance = this;

        window = Window::create(WindowProps(name));
        window->setEventCallback(NQ_BIND_EVENT_FN(Application::onEvent));

        Renderer::init();

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);
    }

    /**
     *
     */
    Application::~Application()
    {
        NQ_PROFILE_FUNCTION();
        Renderer::shutDown();
    }

    /**
     *
     */
    void Application::run()
    {
        NQ_PROFILE_FUNCTION();

        while (running) {
            NQ_PROFILE_SCOPE("Run Loop")

            auto time = static_cast<float>(glfwGetTime());
            TimeStep timeStep = time - lastFrameTime;
            lastFrameTime = time;

            if (!minimized) {
                {
                    NQ_PROFILE_SCOPE("Layers update");

                    for (Layer* l : layerStack) {
                        l->onUpdate(timeStep);
                    }
                }

                imGuiLayer->begin();
                {
                    NQ_PROFILE_SCOPE("Layers ImGui render");
                    for (Layer* l : layerStack) {
                        l->onImGuiRender();
                    }
                }
                imGuiLayer->end();
            }

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
        NQ_PROFILE_FUNCTION();

        EventDispatcher dispatcher(event);

        dispatcher.dispatch<WindowCloseEvent>(NQ_BIND_EVENT_FN(Application::onWindowClosed));
        dispatcher.dispatch<WindowResizeEvent>(NQ_BIND_EVENT_FN(Application::onWindowResized));

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
        NQ_PROFILE_FUNCTION();

        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    /**
     *
     * @param layer
     */
    void Application::pushOverlay(Layer* layer)
    {
        NQ_PROFILE_FUNCTION();

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
        NQ_PROFILE_FUNCTION();

        running = false;
        return true;
    }

    bool Application::onWindowResized(WindowResizeEvent& event)
    {
        NQ_PROFILE_FUNCTION();

        if (event.getWidth() == 0 || event.getHeight() == 0) {
            minimized = true;
            return false;
        }

        minimized = false;
        Renderer::onWindowResize(event.getWidth(), event.getHeight());
        return false;
    }
}