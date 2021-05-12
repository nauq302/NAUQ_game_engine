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
        hv = Texture2D::create("../../Sandbox/res/hv.jpeg");

        FramebufferSpecification spec;
        spec.width = 1024;
        spec.height = 786;
        framebuffer = Framebuffer::create(spec);

    }

    void Editor2DLayer::onDetach()
    {

    }

    void Editor2DLayer::onUpdate(TimeStep ts)
    {
        NQ_PROFILE_FUNCTION();

        /// Update
        cameraController.onUpdate(ts);

        nauq::Renderer2D::resetStats();

        {
            NQ_PROFILE_SCOPE("render prep");
            /// Render
            framebuffer->bind();
            RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            RenderCommand::clear();
        }


        {
            NQ_PROFILE_SCOPE("render draw");
            Renderer2D::beginScene(cameraController.getCamera());
    
            static float t = 0.0f;
            t += ts;
    
            Renderer2D::drawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
            Renderer2D::drawQuad({  0.5f, -0.5f }, { 0.5f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });
    
            Renderer2D::drawRotatedQuad({  0.5f, -0.5f }, { 0.5f, 1.0f }, 1.5f * t, { 0.3f, 0.8f, 0.4f, 1.0f });
    
            Renderer2D::drawRotatedQuad({ 0.0f, 0.0f, 0.1f }, { 1.0f, 1.0f }, 1.0f * t, hv);
    
            Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, hv, 10.0f);
    
            for (float y = -0.5f; y < 5.0f; y += 0.5f) {
                for (float x = -0.5f; x < 5.0f; x += 0.5f) {
                    glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.9f };
                    nauq::Renderer2D::drawQuad({ x, y }, { 0.45f, 0.45f }, color);
                }
            }
            Renderer2D::endScene();
        }

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
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
            ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
            if (!opt_padding)
                ImGui::PopStyleVar();

            if (opt_fullscreen)
                ImGui::PopStyleVar(2);

            // DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, {0.0f, 0.0f}, dockspace_flags);
            }

            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {

                    if (ImGui::MenuItem("Exit")) Application::get().close();

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            {
                ImGui::Begin("Setting");

                auto s = nauq::Renderer2D::getStats();
                ImGui::Text("Renderer 2D stats:");
                ImGui::Text("Draw Calls: %d", s.drawCalls);
                ImGui::Text("Quads: %d", s.quadCount);
                ImGui::Text("Vertices: %d", s.getTotalQuadVertexCount());
                ImGui::Text("Indices: %d", s.getTotalQuadIndexCount());

                ImGui::ColorEdit4("Square Color", glm::value_ptr(sqColor));

                ImGui::End();

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
                ImGui::Begin("Viewport");
                ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
                if (viewportSize != *reinterpret_cast<glm::vec2*>(&viewportPanelSize)) {
                    viewportSize = { viewportPanelSize.x, viewportPanelSize.y };
                    framebuffer->resize(static_cast<uint32_t>(viewportSize.x), static_cast<uint32_t>(viewportSize.y));
                    cameraController.onResize(viewportSize.x, viewportSize.y);
                }

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
