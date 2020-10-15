//
// Created by nauq302 on 05/08/2020.
//

#include "nauq/Application.hpp"

#include <memory>
#include "nauq/Log.hpp"
#include "nauq/imGui/ImGuiLayer.hpp"

#include "nauq/Input.hpp"

namespace nauq {

    /**
     *
     */
    Application::Application() :
        window(Window::create()),
        running(true)
    {
        NAUQ_CORE_ASSERT(instance == nullptr, "Application already exists");
        instance = this;
        window->setEventCallback(NAUQ_BIND_EVENT_FN(Application::onEvent));

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);

        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);


        float vertices[3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.0f,  0.5f, 0.0f
        };

        vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));

        unsigned int indices[3] = {
                0, 1, 2
        };

        indexBuffer.reset(IndexBuffer::create(indices, 3));

        std::string vertexSrc = R"glsl(
            #version 330 core
            #extension GL_ARB_separate_shader_objects: enable

            layout(location = 0) in vec3 pos;
            out vec3 v_pos;

            void main() {
                v_pos = pos* 0.5 + 0.5;
                gl_Position = vec4(pos, 1.0);
            }
        )glsl";

        std::string fragmentSrc = R"glsl(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_pos;
            void main() {
                color = vec4(v_pos, 1.0);
            }
        )glsl";

        shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);

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
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader->bind();
            glBindVertexArray(vertexArray);
            glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : layerStack) {
                layer->onUpdate();
            }

            imGuiLayer->begin();
            for (Layer* layer : layerStack) {
                layer->onImGuiRender();
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

        dispatcher.dispatch<WindowCloseEvent>(NAUQ_BIND_EVENT_FN(Application::onWindowClosed));

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