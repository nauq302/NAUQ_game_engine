//
// Created by nauq302 on 06/10/2020.
//

#include "nauq/platform/openGL/OpenGL_Context.hpp"
#include "nauq/Log.hpp"

namespace nauq {
    OpenGL_Context::OpenGL_Context(GLFWwindow* glfwWindow) :
        windowHandle(glfwWindow)
    {
        NAUQ_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGL_Context::init()
    {
        glfwMakeContextCurrent(windowHandle);

        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        NAUQ_CORE_ASSERT(status, "Failed to initialize Glad!");
    }

    void OpenGL_Context::swapBuffers()
    {
        glfwSwapBuffers(windowHandle);
    }
}

