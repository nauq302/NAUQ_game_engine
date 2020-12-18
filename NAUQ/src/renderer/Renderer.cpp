//
// Created by nauq302 on 06/12/2020.
//

#include <nauq/renderer/RenderCommand.hpp>
#include "nauq/renderer/Renderer.hpp"

namespace nauq {

    Renderer::SceneData Renderer::sceneData;

    void Renderer::beginScene(OrthographicCamera& camera)
    {
        sceneData.viewProjectionMatrix = camera.getViewProjection();
    }

    void Renderer::submit(const std::shared_ptr<Shader>& shader,
                          const std::shared_ptr<VertexArray>& vertexArray,
                          const glm::mat4& transform)
    {
        shader->bind();
        shader->uploadUniform("u_vp", sceneData.viewProjectionMatrix);
        shader->uploadUniform("u_transform", transform);
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

    void Renderer::endScene()
    {

    }
}