//
// Created by nauq302 on 12/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_INPUT_HPP
#define NAUQ_GAME_ENGINE_INPUT_HPP

#include "Core.hpp"
#include "glm/vec2.hpp"

namespace nauq {

    class NAUQ_API Input
    {
    private:
        static Input* instance;
    public:
        static bool isKeyPress(int keycode) { return instance->isKeyPressImpl(keycode); }

        static bool isMouseButtonPress(int button) { return instance->isMouseButtonPressImpl(button); }
        static glm::vec2 getMousePosition() { return instance->getMousePositionImpl(); }
        static float getMouseX() { return instance->getMouseXImpl(); }
        static float getMouseY() { return instance->getMouseYImpl(); }

    protected:
        virtual bool isKeyPressImpl(int keycode) = 0;
        virtual bool isMouseButtonPressImpl(int button) = 0;
        virtual glm::vec2 getMousePositionImpl() = 0;
        virtual inline float getMouseXImpl() { return getMousePositionImpl().x; }
        virtual inline float getMouseYImpl() { return getMousePositionImpl().y; }
    };
}



#endif //NAUQ_GAME_ENGINE_INPUT_HPP
