//
// Created by nauq302 on 05/08/2020.
//

#include "nauq/Application.hpp"

#include <memory>
#include "nauq/Log.hpp"
#include "nauq/imGui/ImGuiLayer.hpp"

#include "nauq/renderer/Renderer.hpp"
#include "nauq/renderer/RenderCommand.hpp"
#include "nauq/Input.hpp"


namespace nauq {

    /**
     *
     */
    Application::Application() :
        camera(-2.0f, 2.0f, -1.5f, 1.5f),
        running(true)
    {
        NAUQ_CORE_ASSERT(instance == nullptr, "Application already exists");
        instance = this;

        window.reset(Window::create());
        window->setEventCallback(NAUQ_BIND_EVENT_FN(Application::onEvent));

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);

        vertexArray.reset(VertexArray::create());

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        };

        std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::create(vertices, sizeof(vertices)));

        vertexBuffer->setLayout({
            { ShaderDataType::VEC3F, "a_pos" },
            { ShaderDataType::VEC4F, "a_color" }
        });

        vertexArray->addVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {
                0, 1, 2
        };

        std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::create(indices, 3));
        vertexArray->setIndexBuffer(indexBuffer);

        squareVA.reset(VertexArray::create());

        float sq[] = {
                -0.75f, -0.75f, 0.0f,
                 0.75f, -0.75f, 0.0f,
                 0.75f,  0.75f, 0.0f,
                -0.75f,  0.75f, 0.0f,
        };

        std::shared_ptr<VertexBuffer> squareVB(VertexBuffer::create(sq, sizeof(sq)));
        squareVB->setLayout({
            { ShaderDataType::VEC3F, "a_pos" }
        });
        squareVA->addVertexBuffer(squareVB);

        unsigned int sqi[] = {
                0, 1, 2, 2, 3, 0
        };
        std::shared_ptr<IndexBuffer> squareIB(IndexBuffer::create(sqi, 6));
        squareVA->setIndexBuffer(squareIB);

        std::string vertexSrc = R"glsl(
            #version 330 core
            #extension GL_ARB_separate_shader_objects: enable

            layout(location = 0) in vec3 a_pos;
            layout(location = 1) in vec4 a_color;

            uniform mat4 u_vp;

            out vec3 v_pos;
            out vec4 v_color;

            void main() {
                v_pos = a_pos * 0.5 + 0.5;
                gl_Position = u_vp * vec4(a_pos, 1.0);
                v_color = a_color;
            }
        )glsl";

        std::string fragmentSrc = R"glsl(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_pos;
            in vec4 v_color;

            void main() {
                //color = vec4(v_pos, 1.0);
                color = v_color;
            }
        )glsl";

        std::string vertexBlue = R"glsl(
            #version 330 core
            #extension GL_ARB_separate_shader_objects: enable

            layout(location = 0) in vec3 a_pos;

            uniform mat4 u_vp;

            out vec3 v_pos;

            void main() {
                v_pos = a_pos;
                gl_Position = u_vp * vec4(a_pos,1.0);
            }
        )glsl";

        std::string fragmentBlue = R"glsl(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_pos;

            void main() {
                color = vec4(0.2,0.3,0.8,1.0);
            }
        )glsl";

        shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
        blueShader = std::make_unique<Shader>(vertexBlue, fragmentBlue);
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
            RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            RenderCommand::clear();

            camera.setPosition({0.5f, 0.5f, 0.0f});
            camera.setRotation(45.f);

            Renderer::beginScene(camera);

            Renderer::submit(blueShader, squareVA);
            Renderer::submit(shader, vertexArray);

            Renderer::endScene();

            for (Layer* l : layerStack) {
                l->onUpdate();
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