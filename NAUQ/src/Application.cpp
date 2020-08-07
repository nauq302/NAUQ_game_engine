//
// Created by nauq302 on 05/08/2020.
//

#include "nauq/Application.hpp"
#include "nauq/Log.hpp"

#include <GLFW/glfw3.h>

namespace nauq {

    Application::Application() : window(Window::create()), running(true) {}

    Application::~Application() = default;

    void Application::run()
    {
        while (running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            window->onUpdate();
        }
    }
}