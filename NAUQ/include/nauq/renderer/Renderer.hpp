//
// Created by nauq302 on 14/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_RENDERER_HPP
#define NAUQ_GAME_ENGINE_RENDERER_HPP

#include "RendererAPI.hpp"
#include "nauq/renderer/OrthographicCamera.hpp"
#include "nauq/renderer/Shader.hpp"

namespace nauq {

    class Renderer
    {
    private:
        struct SceneData {
            glm::mat4 viewProjectionMatrix;
        };

        static SceneData sceneData;

    public:
        static inline RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

        static void beginScene(OrthographicCamera& camera);
        static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.f));
        static void endScene();
    };
}



#endif //NAUQ_GAME_ENGINE_RENDERER_HPP
