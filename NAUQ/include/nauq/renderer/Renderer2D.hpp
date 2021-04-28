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
    private:
        static constexpr glm::mat4 eyes = glm::mat4(1.0f);
        static constexpr glm::vec4 white = glm::vec4(1.0f);

    public:
        static void init();
        static void shutDown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        static void flush();


        static void drawQuad(glm::vec2 pos, glm::vec2 size, const glm::vec4& color);
        static void drawQuad(glm::vec3 pos, glm::vec2 size, const glm::vec4& color);

        static void drawQuad(glm::vec2 pos, glm::vec2 size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white);
        static void drawQuad(glm::vec3 pos, glm::vec2 size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white);

        static void drawRotatedQuad(glm::vec2 pos, glm::vec2 size, float degrees, const glm::vec4& color);
        static void drawRotatedQuad(glm::vec3 pos, glm::vec2 size, float degrees, const glm::vec4& color);
        static void drawRotatedQuad(glm::vec2 pos, glm::vec2 size, float degrees, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white);
        static void drawRotatedQuad(glm::vec3 pos, glm::vec2 size, float degrees, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white);

    };


}




#endif //NAUQ_GAME_ENGINE_RENDERER2D_HPP
