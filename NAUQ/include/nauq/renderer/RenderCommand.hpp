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
        static inline void init() { rendererAPI->init(); }
        static inline void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) { rendererAPI->setViewport(x, y, w, h); }

        static inline void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) { rendererAPI->drawIndexed(vertexArray, count); }

        static inline void setClearColor(const glm::vec4& color) { rendererAPI->setClearColor(color); }
        static inline void setClearColor(float r, float g, float b, float a) { setClearColor({ r, g, b, a }); }

        static inline void clear() { rendererAPI->clear(); }
    };

}


#endif //NAUQ_GAME_ENGINE_RENDERCOMMAND_HPP
