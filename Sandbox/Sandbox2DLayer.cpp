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
    texture = nq::Texture2D::create("../../Sandbox/res/hv.jpeg");
}

void Sandbox2DLayer::onDetach()
{

}

void Sandbox2DLayer::onUpdate(nq::TimeStep ts)
{
    NQ_PROFILE_FUNCTION();

    /// Update
        cameraController.onUpdate(ts);

    {
        NQ_PROFILE_SCOPE("render prep");
        /// Render
        nq::RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        nq::RenderCommand::clear();
    }

    {
        NQ_PROFILE_SCOPE("render draw");
        nq::Renderer2D::beginScene(cameraController.getCamera());

        static float t = 0.0f;
        t += ts;

        nq::Renderer2D::drawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        nq::Renderer2D::drawQuad({  0.5f, -0.5f }, { 0.5f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });

        nq::Renderer2D::drawRotatedQuad({  0.5f, -0.5f }, { 0.5f, 1.0f }, 15.0f * t, { 0.2f, 0.8f, 0.3f, 1.0f });

        nq::Renderer2D::drawRotatedQuad({ 0.0f, 0.0f, 0.1f }, { 1.0f, 1.0f }, 10.0f * t, texture, 1.0f, { 0.5f, 0.0f, 0.0f, 1.0f });

        nq::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, texture, 10.0f, { 0.5f, 0.0f, 0.0f, 1.0f });

        nq::Renderer2D::endScene();
    }

}

void Sandbox2DLayer::onImGuiRender()
{
    NQ_PROFILE_FUNCTION();

    ImGui::Begin("Setting");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(sqColor));

    ImGui::End();
}

void Sandbox2DLayer::onEvent(nq::Event& event)
{
    NQ_PROFILE_FUNCTION();

    cameraController.onEvent(event);
}



