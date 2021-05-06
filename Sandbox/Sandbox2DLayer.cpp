//
// Created by nauq302 on 08/04/2021.
//


#include "Sandbox2DLayer.hpp"

#include <glm/gtc/type_ptr.hpp>


Sandbox2DLayer::Sandbox2DLayer() :
    nq::Layer("Sandbox 2D"),
    cameraController(1024.f / 768.f)
{

}

void Sandbox2DLayer::onAttach()
{
//    hv = nq::Texture2D::create("../../Sandbox/res/hv.jpeg");
    sheet = nq::Texture2D::create("../../Sandbox/res/game_sheet.png");
    test = nq::SubTexture2D::createFromCoords(sheet, { 0, 0 }, { 53, 53 }, { 1, 2 });

    props.colorBegin = { 254 / 255.f, 212 / 255.f, 123 / 255.f, 1.0f };
    props.colorEnd   = { 254 / 255.f, 109 / 255.f,  41 / 255.f, 1.0f };

    props.sizeBegin = 0.5f;
    props.sizeEnd   = 0.0f;
    props.sizeVariation = 0.3f;

    props.lifeTime = 1.0f;

    props.velocity = { 0.0f, 0.0f };
    props.velocityVariation = { 3.0f, 3.0f };

    props.position = { 0.0f, 0.0f };

    cameraController.setZoomLevel(4);
}

void Sandbox2DLayer::onDetach()
{

}

void Sandbox2DLayer::onUpdate(nq::TimeStep ts)
{
    NQ_PROFILE_FUNCTION();

    /// Update
    cameraController.onUpdate(ts);

    nauq::Renderer2D::resetStats();

    {
        NQ_PROFILE_SCOPE("render prep");
        /// Render
        nq::RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        nq::RenderCommand::clear();
    }

#if 0
    {
        NQ_PROFILE_SCOPE("render draw");
        nq::Renderer2D::beginScene(cameraController.getCamera());

        static float t = 0.0f;
        t += ts;

        nq::Renderer2D::drawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        nq::Renderer2D::drawQuad({  0.5f, -0.5f }, { 0.5f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });

        nq::Renderer2D::drawRotatedQuad({  0.5f, -0.5f }, { 0.5f, 1.0f }, 1.5f * t, { 0.3f, 0.8f, 0.4f, 1.0f });

        nq::Renderer2D::drawRotatedQuad({ 0.0f, 0.0f, 0.1f }, { 1.0f, 1.0f }, 1.0f * t, hv);

        nq::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, hv, 10.0f);

        for (float y = -0.5f; y < 5.0f; y += 0.5f) {
            for (float x = -0.5f; x < 5.0f; x += 0.5f) {
                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.9f };
                nauq::Renderer2D::drawQuad({ x, y }, { 0.45f, 0.45f }, color);
            }
        }
        nq::Renderer2D::endScene();
    }
#endif

    nq::Renderer2D::beginScene(cameraController.getCamera());
    nq::Renderer2D::drawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 2.0f }, test);
    nq::Renderer2D::endScene();

    if (nq::Input::isMouseButtonPress(NQ_MOUSE_BUTTON_LEFT)) {
        glm::vec2 m = nq::Input::getMousePosition();
        auto& window = nq::Application::get().getWindow();
        auto width = static_cast<float>(window.getWidth());
        auto height = static_cast<float>(window.getHeight());

        auto bounds = cameraController.getBound();
        auto pos = cameraController.getCamera().getPosition();
        m.x = (m.x / width - 0.5f) * bounds.getWidth();
        m.y = (0.5f - m.y / height) * bounds.getHeight();x`
        props.position = { m.x + pos.x, m.y + pos.y };

        particleSystem.emit(props);
    }

    particleSystem.onUpdate(ts);
    particleSystem.onRender(cameraController.getCamera());
}

void Sandbox2DLayer::onImGuiRender()
{
    NQ_PROFILE_FUNCTION();

    ImGui::Begin("Setting");

    auto s = nauq::Renderer2D::getStats();
    ImGui::Text("Renderer 2D stats:");
    ImGui::Text("Draw Calls: %d", s.drawCalls);
    ImGui::Text("Quads: %d", s.quadCount);
    ImGui::Text("Vertices: %d", s.getTotalQuadVertexCount());
    ImGui::Text("Indices: %d", s.getTotalQuadIndexCount());

    ImGui::ColorEdit4("Square Color", glm::value_ptr(sqColor));

    ImGui::End();
}

void Sandbox2DLayer::onEvent(nq::Event& event)
{
    NQ_PROFILE_FUNCTION();

    cameraController.onEvent(event);
}



