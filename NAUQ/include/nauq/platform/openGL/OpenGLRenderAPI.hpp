//
// Created by nauq302 on 06/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLRENDERAPI_HPP
#define NAUQ_GAME_ENGINE_OPENGLRENDERAPI_HPP

#include "nauq/renderer/RendererAPI.hpp"

namespace nauq {

    class OpenGLRenderAPI :
            public RendererAPI
    {
    public:
        void setClearColor(const glm::vec4& color) override;

        void clear() override;

        void drawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}



#endif //NAUQ_GAME_ENGINE_OPENGLRENDERAPI_HPP
