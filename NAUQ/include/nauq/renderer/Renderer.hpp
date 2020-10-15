//
// Created by nauq302 on 14/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_RENDERER_HPP
#define NAUQ_GAME_ENGINE_RENDERER_HPP

namespace nauq {

    enum class RendererAPI
    {
        NONE = 0,
        OPEN_GL = 1,
    };


    class Renderer
    {
    private:
        inline static RendererAPI api = RendererAPI::OPEN_GL;

    public:
        inline static RendererAPI getAPI() { return api; }
    };
}



#endif //NAUQ_GAME_ENGINE_RENDERER_HPP
