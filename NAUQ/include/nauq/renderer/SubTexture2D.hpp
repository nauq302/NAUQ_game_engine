//
// Created by nauq302 on 06/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_SUBTEXTURE2D_HPP
#define NAUQ_GAME_ENGINE_SUBTEXTURE2D_HPP

#include "nauq/renderer/Texture.hpp"
#include "nauq/core/Log.hpp"
#include <glm/glm.hpp>

namespace nauq {

    class SubTexture2D
    {
    private:
        const Ref<Texture2D>& texture;
        std::array<glm::vec2,4> texCoords;

    public:
        explicit SubTexture2D(const Ref<Texture2D>& texture, glm::vec2 bottomLeft, glm::vec2 topRight);
        ~SubTexture2D() = default;

    public:
        [[nodiscard]] inline const std::array<glm::vec2,4>& getCoords() const { return texCoords; }
        [[nodiscard]] inline const Ref<Texture2D>& getTexture() const { return texture; }


        static Ref<SubTexture2D> createFromCoords(const Ref<Texture2D>& texture, glm::vec2 coords, glm::vec2 ceilSize, glm::vec2 spriteSize = { 1, 1 });
    };
}



#endif //NAUQ_GAME_ENGINE_SUBTEXTURE2D_HPP
