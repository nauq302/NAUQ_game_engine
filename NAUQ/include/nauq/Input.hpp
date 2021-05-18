//
// Created by nauq302 on 12/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_INPUT_HPP
#define NAUQ_GAME_ENGINE_INPUT_HPP

#include "nauq/core/Core.hpp"
#include "glm/vec2.hpp"

namespace nauq {

    class NAUQ_API Input
    {

    public:
        static bool isKeyPress(int keycode);

        static bool isMouseButtonPress(int button);
        static glm::vec2 getMousePosition();
        static float getMouseX();
        static float getMouseY();
    };
}

//namespace std {
//    template<std::size_t length, typename T, glm::qualifier Q>
//    glm::vec<length, T
//}


#endif //NAUQ_GAME_ENGINE_INPUT_HPP
