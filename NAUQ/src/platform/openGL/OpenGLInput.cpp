//
// Created by nauq302 on 12/08/2020.
//

#include "nauq/Input.hpp"

#include "nauq/Application.hpp"

namespace nauq {

    inline GLFWwindow* getWindow() { return static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow()); }

    bool Input::isKeyPress(int keycode)
    {
        int state = glfwGetKey(getWindow(), keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPress(int button)
    {
        int state = glfwGetMouseButton(getWindow(), button);

        return state == GLFW_PRESS;
    }

    glm::vec2 Input::getMousePosition()
    {
        double x, y;
        glfwGetCursorPos(getWindow(), &x, &y);
        return { x, y };
    }

    float Input::getMouseX()
    {
        double x;
        glfwGetCursorPos(getWindow(), &x, nullptr);
        return static_cast<float>(x);
    }

    float Input::getMouseY()
    {
        double y;
        glfwGetCursorPos(getWindow(), nullptr, &y);
        return static_cast<float>(y);
    }

}