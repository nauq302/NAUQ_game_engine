//
// Created by nauq302 on 08/04/2021.
//


#include "Editor2DLayer.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace nauq {


    Editor2DLayer::Editor2DLayer() :
            Layer("Sandbox 2D"),
            cameraController(1024.f / 768.f)
    {

    }

    void Editor2DLayer::onAttach()
    {
        hv = Texture2D::create("../../Editor/res/moon.png");

        FramebufferSpecification spec;
        spec.width = 1024;
        spec.height = 786;
        framebuffer = Framebuffer::create(spec);

        activeScene = createRef<Scene>();

        square = activeScene->createEntity("Square");
        square.add<SpriteRendererComponent>(glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f });

        redSquare = activeScene->createEntity("RedSquare");
        redSquare.add<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.3f, 0.2f, 1.0f });

        camEntity = activeScene->createEntity("Camera 1");
        camEntity.add<CameraComponent>();

        camEntity2 = activeScene->createEntity("Camera 2");
        camEntity2.add<CameraComponent>();



        class CameraController :
                public ScriptableEntity
        {
        public:
            void onCreate() override
            {
                get<TransformComponent>().transform[3][0] = rand() % 10;
            }

            void onDestroy() override
            {

            }

            void onUpdate(TimeStep ts) override
            {
                auto& transform = get<TransformComponent>().transform;
                float speed = 5.0f;

                if (Input::isKeyPress(NQ_KEY_A))
                    transform[3][0] -= speed * ts;
                if (Input::isKeyPress(NQ_KEY_D))
                    transform[3][0] += speed * ts;
                if (Input::isKeyPress(NQ_KEY_W))
                    transform[3][1] += speed * ts;
                if (Input::isKeyPress(NQ_KEY_S))
                    transform[3][1] -= speed * ts;

            }
        };

        camEntity.add<NativeScriptComponent>().bind<CameraController>();
        camEntity2.add<NativeScriptComponent>().bind<CameraController>();

        sceneHierarchyPanel.setContext(activeScene);
    }

    void Editor2DLayer::onDetach()
    {

    }

    void Editor2DLayer::onUpdate(TimeStep ts)
    {
        NQ_PROFILE_FUNCTION();

        FramebufferSpecification spec = framebuffer->getSpecification();
        if (viewportSize.x > 0.0f && viewportSize.y > 0.0f && (spec.width != viewportSize.x || spec.height != viewportSize.y)) {
            framebuffer->resize(static_cast<uint32_t>(viewportSize.x), static_cast<uint32_t>(viewportSize.y));
            cameraController.onResize(viewportSize.x, viewportSize.y);
            activeScene->onViewportResize(static_cast<uint32_t>(viewportSize.x), static_cast<uint32_t>(viewportSize.y));
        }

        /// Update
        if (viewportFocused)
            cameraController.onUpdate(ts);

        /// Render
        nauq::Renderer2D::resetStats();
        framebuffer->bind();
        RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        RenderCommand::clear();

        activeScene->onUpdate(ts);

        framebuffer->unbind();
    }

    void Editor2DLayer::onImGuiRender()
    {
        NQ_PROFILE_FUNCTION();

        static bool dockSpaceEnabled = true;

        if (dockSpaceEnabled) {
            static bool dockSpaceOpen = true;
            static bool opt_fullscreen = true;
            static bool opt_padding = false;
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen) {
                ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->GetWorkPos());
                ImGui::SetNextWindowSize(viewport->GetWorkSize());
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

            } else {
                dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
            }

            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            if (!opt_padding)
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
            ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
            if (!opt_padding)
                ImGui::PopStyleVar();

            if (opt_fullscreen)
                ImGui::PopStyleVar(2);

            // DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, { 0.0f, 0.0f }, dockspace_flags);
            }

            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Exit"))
                        Application::get().close();
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            sceneHierarchyPanel.onImGuiRender();

            {
                ImGui::Begin("Setting");

                auto s = nauq::Renderer2D::getStats();
                ImGui::Text("Renderer 2D stats:");
                ImGui::Text("Draw Calls: %d", s.drawCalls);
                ImGui::Text("Quads: %d", s.quadCount);
                ImGui::Text("Vertices: %d", s.getTotalQuadVertexCount());
                ImGui::Text("Indices: %d", s.getTotalQuadIndexCount());

                auto& sqColor = square.get<SpriteRendererComponent>().color;
                ImGui::ColorEdit4("Square Color", glm::value_ptr(sqColor));

                ImGui::DragFloat3("Camera Transform", glm::value_ptr(camEntity2.get<TransformComponent>().transform[3]));

                if (ImGui::Checkbox("Camera 1", &primaryCam)) {
                    camEntity.get<CameraComponent>().primary = primaryCam;
                    camEntity2.get<CameraComponent>().primary = !primaryCam;
                }

                ImGui::End();

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
                ImGui::Begin("Viewport");
                viewportFocused = ImGui::IsWindowFocused();
                viewportHovered = ImGui::IsWindowHovered();
                bool allowEvent = viewportFocused && viewportHovered;
                Application::get().getImGuiLayer()->setBlockEvents(!allowEvent);

                ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
                viewportSize = { viewportPanelSize.x, viewportPanelSize.y };


                uint32_t id = framebuffer->getColorAttachment();
                ImGui::Image(reinterpret_cast<void*>(id), viewportPanelSize, { 0, 1 }, { 1, 0 });
                ImGui::End();
                ImGui::PopStyleVar();
            }

            ImGui::End();

        } else {
            ImGui::Begin("Setting");

            auto s = nauq::Renderer2D::getStats();
            ImGui::Text("Renderer 2D stats:");
            ImGui::Text("Draw Calls: %d", s.drawCalls);
            ImGui::Text("Quads: %d", s.quadCount);
            ImGui::Text("Vertices: %d", s.getTotalQuadVertexCount());
            ImGui::Text("Indices: %d", s.getTotalQuadIndexCount());

            auto& sqColor = square.get<SpriteRendererComponent>().color;
            ImGui::ColorEdit4("Square Color", glm::value_ptr(sqColor));
            std::uint32_t id = hv->getRendererID();
            ImGui::Image(reinterpret_cast<void*>(id), { 64.0f, 64.0f }, { 0, 1 }, { 1, 0 });

            ImGui::End();
        }


    }

    void Editor2DLayer::onEvent(Event& event)
    {
        NQ_PROFILE_FUNCTION();

        cameraController.onEvent(event);
    }


}
