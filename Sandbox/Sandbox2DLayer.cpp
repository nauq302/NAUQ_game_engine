//
// Created by nauq302 on 08/04/2021.
//


#include "Sandbox2DLayer.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <nauq/platform/openGL/OpenGLShader.hpp>


Sandbox2DLayer::Sandbox2DLayer() :
    nq::Layer("Sandbox 2D"),
    cameraController(1024.f / 768.f)
{

}

void Sandbox2DLayer::onAttach()
{

}

void Sandbox2DLayer::onDetach()
{

}

void Sandbox2DLayer::onUpdate(nq::TimeStep ts)
{
    /// Update
    cameraController.onUpdate(ts);

    /// Render
    nq::RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    nq::RenderCommand::clear();

    nq::Renderer2D::beginScene(cameraController.getCamera());

    nq::Renderer2D::drawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });


    nq::Renderer2D::endScene();

//    static const glm::mat4 eyes(1.0f);
//    auto fc = std::dynamic_pointer_cast<nq::OpenGLShader>(shader);
//    fc->bind();
//    fc->uploadUniform("u_color", sqColor);

//    auto tr = glm::scale(eyes, glm::vec3(1.5f));
//
//    shader->bind();
//    nq::Renderer::submit(shader, vertexArray, tr);


}

void Sandbox2DLayer::onImGuiRender()
{
    ImGui::Begin("Setting");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(sqColor));
    ImGui::End();
}

void Sandbox2DLayer::onEvent(nq::Event& event)
{
    cameraController.onEvent(event);
}



