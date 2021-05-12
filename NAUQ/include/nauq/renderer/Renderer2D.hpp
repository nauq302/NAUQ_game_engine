//
// Created by nauq302 on 09/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_RENDERER2D_HPP
#define NAUQ_GAME_ENGINE_RENDERER2D_HPP

#include "OrthographicCamera.hpp"
#include "Texture.hpp"
#include "SubTexture2D.hpp"

namespace nauq {

    class Renderer2D
    {
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

        static void drawQuad(glm::vec2 pos, glm::vec2 size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white);
        static void drawQuad(glm::vec3 pos, glm::vec2 size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white);

        static void drawRotatedQuad(glm::vec2 pos, glm::vec2 size, float radians, const glm::vec4& color);
        static void drawRotatedQuad(glm::vec3 pos, glm::vec2 size, float radians, const glm::vec4& color);
        static void drawRotatedQuad(glm::vec2 pos, glm::vec2 size, float radians, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white);
        static void drawRotatedQuad(glm::vec3 pos, glm::vec2 size, float radians, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white);

        struct Statistics
        {
            uint32_t drawCalls = 0;
            uint32_t quadCount = 0;

            [[nodiscard]] inline uint32_t getTotalQuadVertexCount() const { return quadCount * 4; }
            [[nodiscard]] inline uint32_t getTotalQuadIndexCount() const { return quadCount * 6; }
        };

        static Statistics getStats();
        static void resetStats();

    private:
        static void flushAndReset();
    };
}




#endif //NAUQ_GAME_ENGINE_RENDERER2D_HPP
