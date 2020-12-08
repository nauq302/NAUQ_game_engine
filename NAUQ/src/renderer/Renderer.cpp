//
// Created by nauq302 on 06/12/2020.
//

#include <nauq/renderer/RenderCommand.hpp>
#include "nauq/renderer/Renderer.hpp"

namespace nauq {

    void Renderer::beginScene()
    {

    }

    void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

    void Renderer::endScene()
    {

    }
}