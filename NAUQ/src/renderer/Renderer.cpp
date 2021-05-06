//
// Created by nauq302 on 06/12/2020.
//

#include <nauq/renderer/RenderCommand.hpp>
#include "nauq/renderer/Renderer.hpp"
#include "nauq/renderer/Renderer2D.hpp"
#include "nauq/debug/Instrumentor.hpp"

#include "nauq/platform/openGL/OpenGLShader.hpp"

namespace nauq {

    Renderer::SceneData Renderer::sceneData;

    void Renderer::init()
    {
        NQ_PROFILE_FUNCTION();

        RenderCommand::init();
        Renderer2D::init();
    }

    void Renderer::onWindowResize(std::uint32_t width, std::uint32_t height)
    {
        RenderCommand::setViewport(0, 0, width, height);
    }

    void Renderer::beginScene(OrthographicCamera& camera)
    {
        sceneData.viewProjectionMatrix = camera.getViewProjection();
    }

    void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->bind();
        auto sd = std::dynamic_pointer_cast<OpenGLShader>(shader);

        sd->uploadUniform("u_vp", sceneData.viewProjectionMatrix);
        sd->uploadUniform("u_transform", transform);
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

    void Renderer::endScene()
    {

    }

    void Renderer::shutDown()
    {
        Renderer2D::shutDown();
    }


}