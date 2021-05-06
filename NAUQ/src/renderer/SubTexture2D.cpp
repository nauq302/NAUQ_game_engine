//
// Created by nauq302 on 06/05/2021.
//

#include "nauq/renderer/SubTexture2D.hpp"

namespace nauq {

    SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, glm::vec2 bottomLeft, glm::vec2 topRight) :
        texture(texture),
        texCoords {
                bottomLeft,
                { topRight.x  , bottomLeft.y },
                { topRight.x  , topRight.y },
                { bottomLeft.x, topRight.y },
        }
    {

    }

    Ref<SubTexture2D> SubTexture2D::createFromCoords(const Ref<Texture2D>& texture, glm::vec2 coords, glm::vec2 ceilSize, glm::vec2 spriteSize)
    {
        glm::vec2 ratio = { ceilSize.x / texture->getWidth(), ceilSize.y / texture->getHeight() };

        glm::vec2 bottomLeft = { coords.x * ratio.x, coords.y * ratio.y };
        glm::vec2 topRight = { (coords.x + spriteSize.x) * ratio.x, (coords.y + spriteSize.y) * ratio.y };

        return createRef<SubTexture2D>(texture, bottomLeft, topRight);
    }


}