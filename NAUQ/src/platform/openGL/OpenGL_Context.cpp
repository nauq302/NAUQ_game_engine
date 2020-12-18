//
// Created by nauq302 on 06/10/2020.
//

#include "nauq/platform/openGL/OpenGL_Context.hpp"
#include "nauq/Log.hpp"

namespace nauq {

    OpenGL_Context::OpenGL_Context(GLFWwindow* glfwWindow) :
        windowHandle(glfwWindow)
    {
        NQ_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGL_Context::init()
    {
        glfwMakeContextCurrent(windowHandle);

        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        NQ_CORE_ASSERT(status, "Failed to initialize Glad!");

        NQ_CORE_INFO("OpenGL Info:");
        NQ_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
        NQ_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
        NQ_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));
    }

    void OpenGL_Context::swapBuffers()
    {
        glfwSwapBuffers(windowHandle);
    }
}

