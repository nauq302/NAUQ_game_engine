//
// Created by nauq302 on 08/04/2021.
//


#include "Sandbox2DLayer.hpp"

#include <glm/gtc/type_ptr.hpp>

static const std::uint32_t mapWidth = 25;
static const std::uint32_t mapHeight = 20;
static constexpr glm::vec2 ceilSize = { 16, 16 };
static const char* mapTile =
        "wwwwwwwwwwwwwwwwwwwwwwwww"
        "wwwwwwwwwdddddddwwwwwwwww"
        "wwwwwwwddwdddddddddwwwwww"
        "wwwwwwdddddddddwwwwwwwwww"
        "wwwwwwwwwwwdddddddwwwwwww"
        "wwwwwwwwwwwwwwwwwwwwwwwww"
        "wwwwwwwwwdddddddwwwwwwwww"
        "wwwwwwwddwdddddddddwwwwww"
        "wwwwwwdddddddddwwwwwwwwww"
        "wwwwwwwwwwwdddddddwwwwwww"
        "wwwwwwwwwwwwwwwwwwwwwwwww"
        "wwwwwwwwwdddddddwwwwwwwww"
        "wwwwwwwddwdddddddddwwwwww"
        "wwwwwwdddddddddwwwwwwwwww"
        "wwwwwwwwwwwdddddddwwwwwww"
        "wwwwwwwwwwwwwwwwwwwwwwwww"
        "wwwwwwwwwdddddddwwwwwwwww"
        "wwwwwwwddwdddddddddwwwwww"
        "wwwwwwdddddddddwwwwwwwwww"
        "wwwwwwwwwwwdddddddwwwwwww";

Sandbox2DLayer::Sandbox2DLayer() :
    nq::Layer("Sandbox 2D"),
    cameraController(1024.f / 768.f)
{

}

void Sandbox2DLayer::onAttach()
{
    hv = nq::Texture2D::create("../../Sandbox/res/hv.jpeg");
    sheet = nq::Texture2D::create("../../Sandbox/res/urban_sheet.png");
    test = nq::SubTexture2D::createFromCoords(sheet, { 0, 12 }, ceilSize, { 1, 3 });

    textures.insert({'w', nq::SubTexture2D::createFromCoords(sheet, { 9, 10 }, ceilSize, { 1, 1 })});
    textures.insert({'d', nq::SubTexture2D::createFromCoords(sheet, { 1, 13 }, ceilSize, { 1, 1 })});

    nq::FramebufferSpecification spec;
    spec.width = 1024;
    spec.height = 786;

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
    for (std::uint32_t y = 0; y < mapHeight; ++y) {
        for (std::uint32_t x = 0; x < mapWidth; ++x) {
            nq::Renderer2D::drawQuad({ x, y }, { 1.0f, 1.0f }, textures[mapTile[x + y * mapWidth]]);
        }
    }
    nq::Renderer2D::endScene();
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
    std::uint32_t id = hv->getRendererID();
    ImGui::Image(reinterpret_cast<void*>(id), { 64.0f, 64.0f }, { 0, 1 }, { 1, 0 });

    ImGui::End();
}

void Sandbox2DLayer::onEvent(nq::Event& event)
{
    NQ_PROFILE_FUNCTION();

    cameraController.onEvent(event);
}



