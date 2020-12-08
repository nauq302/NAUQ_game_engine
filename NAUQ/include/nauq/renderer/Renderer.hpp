//
// Created by nauq302 on 14/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_RENDERER_HPP
#define NAUQ_GAME_ENGINE_RENDERER_HPP

#include "RendererAPI.hpp"

namespace nauq {

    class Renderer
    {
    private:


    public:
        static inline RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

        static void beginScene();
        static void submit(const std::shared_ptr<VertexArray>& vertexArray);
        static void endScene();
    };
}



#endif //NAUQ_GAME_ENGINE_RENDERER_HPP
