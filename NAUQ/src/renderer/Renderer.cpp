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

    void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->bind();
        shader->uploadUniform("u_vp", sceneData.viewProjectionMatrix);
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

    void Renderer::endScene()
    {

    }
}