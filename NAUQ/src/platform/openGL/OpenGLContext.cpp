//
// Created by nauq302 on 06/10/2020.
//

#include "nauq/platform/openGL/OpenGLContext.hpp"

#include "nauq/debug/Instrumentor.hpp"
#include "nauq/core/Log.hpp"

namespace nauq {

    OpenGLContext::OpenGLContext(GLFWwindow* glfwWindow) :
        windowHandle(glfwWindow)
    {
        NQ_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGLContext::init()
    {
        NQ_PROFILE_FUNCTION();

        glfwMakeContextCurrent(windowHandle);

        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        NQ_CORE_ASSERT(status, "Failed to initialize Glad!");

        NQ_CORE_INFO("OpenGL Info:");
        NQ_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
        NQ_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
        NQ_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));

#ifdef NQ_ENABLE_ASSERTS
        int majorVer;
        int minorVer;
        glGetIntegerv(GL_MAJOR_VERSION, &majorVer);
        glGetIntegerv(GL_MINOR_VERSION, &minorVer);

        NQ_CORE_ASSERT(majorVer > 4 || (majorVer == 4 && minorVer >= 5), "Nauq requires at least OpenGL version 4.5");
#endif
    }

    void OpenGLContext::swapBuffers()
    {
        NQ_PROFILE_FUNCTION();

        glfwSwapBuffers(windowHandle);
    }
}

