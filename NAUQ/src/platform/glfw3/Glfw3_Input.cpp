//
// Created by nauq302 on 12/08/2020.
//

#include "nauq/platform/glfw3/Glfw3_Input.hpp"

#include "nauq/Application.hpp"

namespace nauq {

    Input* Input::instance = new Linux_Input;

    bool Linux_Input::isKeyPressImpl(int keycode)
    {
        auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());

        int state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Linux_Input::isMouseButtonPressImpl(int button)
    {
        auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());

        int state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    glm::vec2 Linux_Input::getMousePositionImpl()
    {
        auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        double x,y;

        glfwGetCursorPos(window, &x, &y);
        return { x, y };
    }



}