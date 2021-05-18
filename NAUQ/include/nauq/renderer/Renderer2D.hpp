//
// Created by nauq302 on 09/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_RENDERER2D_HPP
#define NAUQ_GAME_ENGINE_RENDERER2D_HPP

#include "Camera.hpp"
#include "OrthographicCamera.hpp"
#include "Texture.hpp"
#include "SubTexture2D.hpp"

namespace nauq {

#define COLOR_PARAMS const glm::vec4& color
#define TEXTURE_PARAMS const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white
#define SUB_TEXTURE_PARAMS const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = white

    class Renderer2D
    {
    public:
        static void init();
        static void shutDown();

        static void beginScene(const Camera& camera, const glm::mat4& transform);
        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        static void flush();

        static void drawQuad(glm::vec2 pos, glm::vec2 size, COLOR_PARAMS);
        static void drawQuad(glm::vec3 pos, glm::vec2 size, COLOR_PARAMS);
        static void drawQuad(const glm::mat4& transform, COLOR_PARAMS);

        static void drawQuad(glm::vec2 pos, glm::vec2 size, TEXTURE_PARAMS);
        static void drawQuad(glm::vec3 pos, glm::vec2 size, TEXTURE_PARAMS);
        static void drawQuad(const glm::mat4& transform, TEXTURE_PARAMS);

        static void drawQuad(glm::vec2 pos, glm::vec2 size, SUB_TEXTURE_PARAMS);
        static void drawQuad(glm::vec3 pos, glm::vec2 size, SUB_TEXTURE_PARAMS);

        static void drawRotatedQuad(glm::vec2 pos, glm::vec2 size, float radians, COLOR_PARAMS);
        static void drawRotatedQuad(glm::vec3 pos, glm::vec2 size, float radians, COLOR_PARAMS);
        static void drawRotatedQuad(glm::vec2 pos, glm::vec2 size, float radians, TEXTURE_PARAMS);
        static void drawRotatedQuad(glm::vec3 pos, glm::vec2 size, float radians, TEXTURE_PARAMS);

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
