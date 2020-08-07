//
// Created by nauq302 on 07/08/2020.
//

#include "nauq/platform/Linux_Window.hpp"

#include "nauq/Log.hpp"

namespace nauq {

    static bool glfwInitialized = false;

    Window* Window::create(const WindowProps& props)
    {
        return new Linux_Window(props);
    }

    Linux_Window::Linux_Window(const nauq::WindowProps& props)
    {
        init(props);
    }

    Linux_Window::~Linux_Window()
    {
        glfwDestroyWindow(window);
    }

    void Linux_Window::init(const WindowProps& props)
    {
        data.title = props.title;
        data.width = props.width;
        data.height = props.height;

        NAUQ_CORE_INFO("Create window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!glfwInitialized) {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();
            NAUQ_CORE_ASSERT(success, "Could not initialize GLFW");

            glfwInitialized = true;
        }

        window = glfwCreateWindow(static_cast<int>(data.width), static_cast<int>(data.height), data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, &data);
        setVSync(true);
    }

    void Linux_Window::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    void Linux_Window::setVSync(bool enable)
    {
        if (enable) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        data.vSync = enable;
    }

    bool Linux_Window::isVSync() const
    {
        return data.vSync;
    }



    void Linux_Window::shutdown()
    {

    }
}

