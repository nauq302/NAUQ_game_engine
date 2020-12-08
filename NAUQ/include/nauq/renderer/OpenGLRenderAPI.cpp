//
// Created by nauq302 on 06/12/2020.
//

#include "OpenGLRenderAPI.hpp"

namespace nauq {

    void OpenGLRenderAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.g);
    }

    void OpenGLRenderAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }

}


