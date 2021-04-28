//
// Created by nauq302 on 06/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_RENDERERAPI_HPP
#define NAUQ_GAME_ENGINE_RENDERERAPI_HPP

#include "glm/glm.hpp"
#include "VertexArray.hpp"

namespace nauq {

    class RendererAPI
    {
    public:
        enum class API
        {
            NONE = 0,
            OPEN_GL = 1,
        };

    private:
        inline static API api = API::OPEN_GL;

    public:
        virtual void init() = 0;
        virtual void setViewport(std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h) = 0;
        virtual void setClearColor(const glm::vec4& color) = 0;

        virtual void clear() = 0;
        virtual void drawIndexed(const Ref<VertexArray>& vertexArray, std::uint32_t count = 0) = 0;

        inline static API getAPI() { return api; }
    };
}




#endif //NAUQ_GAME_ENGINE_RENDERERAPI_HPP
