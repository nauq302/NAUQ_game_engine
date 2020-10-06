//
// Created by nauq302 on 12/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_LINUX_INPUT_HPP
#define NAUQ_GAME_ENGINE_LINUX_INPUT_HPP

#include "../../Input.hpp"

namespace nauq {
    class GLfw3_Input :
            public Input
    {
    protected:
        bool isKeyPressImpl(int keycode) override;
        bool isMouseButtonPressImpl(int button) override;

        glm::vec2 getMousePositionImpl() override;
    };
}



#endif //NAUQ_GAME_ENGINE_LINUX_INPUT_HPP
