//
// Created by nauq302 on 06/12/2020.
//

#include "nauq/platform/openGL/OpenGLRenderAPI.hpp"

#include "nauq/debug/Instrumentor.hpp"

namespace nauq {

    void OpenGLRenderAPI::init()
    {
        NQ_PROFILE_FUNCTION();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderAPI::setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
    {
        glViewport(x, y, w, h);
    }

    void OpenGLRenderAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.g);
    }

    void OpenGLRenderAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
    {
        std::uint32_t indexCount = count == 0 ? vertexArray->getIndexBuffer()->getCount() : count;
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }




}


