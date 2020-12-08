//
// Created by nauq302 on 06/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_RENDERCOMMAND_HPP
#define NAUQ_GAME_ENGINE_RENDERCOMMAND_HPP

#include "RendererAPI.hpp"

namespace nauq {


    class RenderCommand
    {
    private:
        static RendererAPI* rendererAPI;

    public:
        static inline void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { rendererAPI->drawIndexed(vertexArray); }

        static inline void setClearColor(const glm::vec4& color) { rendererAPI->setClearColor(color); }
        static inline void setClearColor(float r, float g, float b, float a) { setClearColor({ r, g, b, a}); }

        static inline void clear() { rendererAPI->clear(); }
    };

}


#endif //NAUQ_GAME_ENGINE_RENDERCOMMAND_HPP
