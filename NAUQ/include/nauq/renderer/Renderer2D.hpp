//
// Created by nauq302 on 09/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_RENDERER2D_HPP
#define NAUQ_GAME_ENGINE_RENDERER2D_HPP

#include "OrthographicCamera.hpp"
#include "Texture.hpp"

namespace nauq {

    class Renderer2D
    {
    public:
        static void init();
        static void shutDown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();


        static void drawQuad(glm::vec2 pos, glm::vec2 size, const glm::vec4& color);
        static void drawQuad(glm::vec3 pos, glm::vec2 size, const glm::vec4& color);

        static void drawQuad(glm::vec2 pos, glm::vec2 size, const Ref<Texture>& texture);
        static void drawQuad(glm::vec3 pos, glm::vec2 size, const Ref<Texture>& texture);

    };

}




#endif //NAUQ_GAME_ENGINE_RENDERER2D_HPP
